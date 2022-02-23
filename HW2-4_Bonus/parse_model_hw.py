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
'''
def _onnx_graph_index(graph_prop_list, prop, by_name=False):
      for i, n in enumerate(graph_prop_list):
         if by_name:
            if n.name == prop.name:
                return i
            else:
                if n == prop:
                    return i
      return -1
'''

def number_of_multiplication(dims_list):
        
        if (dims_list[0][2]==dims_list[1][2] and dims_list[0][3]==dims_list[1][3]):
             a=dims_list[0][2]*dims_list[0][3]
        else:
             a=dims_list[0][2]*dims_list[0][3]*dims_list[1][2]*dims_list[1][3]
        return a*dims_list[1][1]*dims_list[1][0]


## find all `Conv` operators and print its input information
for i in onnx_model.graph.node:
    if (i.op_type == 'Conv'):
        D=[]
        print('\n-- Conv "{}" --'.format(i.name))
        for j in i.input:
            if j in input_nlist:
                idx = input_nlist.index(j)
                (dims, size) = get_size(onnx_model.graph.input[idx].type.tensor_type.shape)
                print('input {} has {} elements dims = {}'.format(j, size, dims  ))
                #print(1)
            elif j in initializer_nlist:
                idx = initializer_nlist.index(j)
                (dims, size) = get_size(onnx_model.graph.initializer[idx].type.tensor_type.shape)
                print('input {} has {} elements dims = {}'.format(j, size, dims))
                #print(2)
            elif j in value_info_nlist:
                idx = value_info_nlist.index(j)
                (dims, size) = get_size(onnx_model.graph.value_info[idx].type.tensor_type.shape)
                print('input {} has {} elements dims = {}'.format(j, size, dims))
                #print(3)
            D.append(dims)
        print('number of multiplication is {}'.format(number_of_multiplication(D)))
