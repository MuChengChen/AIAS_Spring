.
├── memory-mapped-hardware
│   ├── build.sbt
│   ├── build.sc
│   ├── build.sh
│   ├── out
│   │   └── mill-profile.json
│   └── src
│       ├── main
│       │   ├── resource
│       │   │   ├── SystolicArray
│       │   │   │   ├── data.hex
│       │   │   │   ├── inst.asm
│       │   │   │   ├── LocalMem.hex
│       │   │   │   └── m_code.hex
│       │   │   └── VectorCPU
│       │   │       ├── data.hex
│       │   │       ├── inst.asm
│       │   │       └── m_code.hex
│       │   └── scala
│       │       └── aias_lab9
│       │           ├── AXI_lite
│       │           │   ├── AXILiteDefs.scala
│       │           │   ├── AXILiteXBar.scala
│       │           │   ├── AXIReadBus.scala
│       │           │   ├── AXISlaveReadMux.scala
│       │           │   ├── AXISlaveWriteMux.scala
│       │           │   └── AXIWriteBus.scala
│       │           ├── Memory
│       │           │   └── DataMem.scala
│       │           ├── SystolicArray
│       │           │   ├── buffer.scala
│       │           │   ├── Memory_Mapped
│       │           │   │   ├── LocalMem.scala
│       │           │   │   ├── Memory_Mapped.scala
│       │           │   │   └── MMIO_Regfile.scala
│       │           │   ├── SA.scala
│       │           │   ├── tile
│       │           │   │   ├── PE.scala
│       │           │   │   └── tile.scala
│       │           │   └── topSA.scala
│       │           ├── topSystolicArray.scala
│       │           ├── topVectorCPU.scala
│       │           └── VectorCPU
│       │               ├── Controller
│       │               │   └── Controller.scala
│       │               ├── Datapath
│       │               │   ├── ALU.scala
│       │               │   ├── BranchComp.scala
│       │               │   ├── ImmGen.scala
│       │               │   ├── PC.scala
│       │               │   ├── RegFile.scala
│       │               │   ├── Vector_ALU.scala
│       │               │   └── Vector_RegFile.scala
│       │               ├── Memory
│       │               │   └── InstMem.scala
│       │               ├── RiscvDefs.scala
│       │               └── VectorCPU.scala
│       └── test
│           └── scala
│               └── aias_lab9
│                   ├── AXI_lite
│                   │   ├── AXILiteXBarTest.scala
│                   │   ├── AXIReadBusTest.scala
│                   │   ├── AXISlaveReadMuxTest.scala
│                   │   ├── AXISlaveWriteMuxTest.scala
│                   │   └── AXIWriteBusTest.scala
│                   ├── SystolicArray
│                   │   ├── bufferTest.scala
│                   │   ├── Memory_MappedTest.scala
│                   │   ├── MMIO_RegfileTest.scala
│                   │   ├── PETest.scala
│                   │   ├── SATest.scala
│                   │   ├── tileTest.scala
│                   │   └── topSATest.scala
│                   ├── topSystolicArrayTest.scala
│                   └── topVectorCPUTest.scala
└── memory-mapped-software
    ├── emulator.cpp
    ├── emulator.h
    ├── linenoise.hpp
    ├── Makefile
    ├── memory_mapped.S
    ├── obj
    │   └── emulator
    ├── translate.cpp
    └── translate.h

25 directories, 61 files
