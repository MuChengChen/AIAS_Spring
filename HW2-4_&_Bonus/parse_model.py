## parse_model.py

import onnx

onnx_model = onnx.load('./lenet.onnx')

## need to run shape inference in order to get a full value_info list
onnx_model = onnx.shape_inference.infer_shapes(onnx_model)

## List all tensor names in the raph
input_nlist = [k.name for k in onnx_model.graph.input]
initializer_nlist = [k.name for k in onnx_model.graph.initializer]
value_info_nlist = [k.name for k in onnx_model.graph.value_info]

print('\ninput list: {}'.format(input_nlist))
print('\ninitializer list: {}'.format(initializer_nlist))
print('\nvalue_info list: {}'.format(value_info_nlist))

## a simple function to calculate the tensor size and extract dimension information
def get_size(shape):
    dims = []
    ndim = len(shape.dim)
    size = 1;
    for i in range(ndim):
        size = size * shape.dim[i].dim_value
        dims.append(shape.dim[i].dim_value)
    return dims, size

## find all `Conv` operators and print its input information
for i in onnx_model.graph.node:
    if (i.op_type == 'Conv'):
        print('\n-- Conv "{}" --'.format(i.name))
        for j in i.input:
            if j in input_nlist:
                idx = input_nlist.index(j)
                (dims, size) = get_size(onnx_model.graph.input[idx].type.tensor_type.shape)
                print('input {} has {} elements dims = {}'.format(j, size, dims  ))
            elif j in initializer_nlist:
                idx = initializer_nlist.index(j)
                (dims, size) = get_size(onnx_model.graph.initializer[idx].type.tensor_type.shape)
                print('input {} has {} elements dims = {}'.format(j, size, dims))
            elif j in value_info_nlist:
                idx = value_info_nlist.index(j)
                (dims, size) = get_size(onnx_model.graph.value_info[idx].type.tensor_type.shape)
                print('input {} has {} elements dims = {}'.format(j, size, dims))
