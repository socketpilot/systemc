# systemc
# SystemC Learning & Modeling Repository

A personal repository for learning, experimenting, and developing SystemC models ranging from basic concepts to virtual platform and transaction-level modeling examples.

The goal of this repository is not only to implement functionality but also to understand **how SystemC models are architected**, how communication occurs between modules, and how hardware/software systems can be represented using SystemC.

---

## Objectives

This repository is used to explore and practice:

- SystemC fundamentals
- Process modeling (`SC_THREAD`, `SC_METHOD`, `SC_CTHREAD`)
- Module hierarchy
- Ports and interfaces
- `sc_port` and `sc_export`
- Event-driven synchronization
- Channel modeling
- FIFO communication
- Register modeling
- TLM concepts
- Virtual prototyping ideas
- Protocol modeling
- Scheduler behavior

---

## Repository Structure

```text
systemC/projects
│
├── producer_consumer/
├── fifo_examples/
├── sc_method_examples/
├── tlm_examples/
├── protocol_models/
├── virtual_platform/
└── README.md