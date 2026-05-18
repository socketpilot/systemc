\# A simple SystemC Producer–Consumer Model using `sc\_port` and `sc\_export`



\## Overview

This project structure having header, source and ws(workspace)

This project implements the classical Producer–Consumer problem in SystemC(3.0.2) using:



\- `sc\_port`

\- `sc\_export`

\- custom interface (`sc\_interface`)

\- event-based synchronization

\- bounded FIFO buffer



The goal of the project is to understand how communication and synchronization are modeled in SystemC while learning the interaction between active and passive components.



\---



\## Learning Objectives



This project was created to understand:



\- How `sc\_port` and `sc\_export` are connected

\- How custom interfaces are defined using `sc\_interface`

\- Separation of responsibilities in SystemC models

\- Active vs Passive components

\- Event-driven synchronization

\- Classical Producer–Consumer behavior

\- Usage of `SC\_THREAD`

\- Buffer state transitions



\---



\## System Architecture



```text

+-------------+         +-------------+         +-------------+

|  Producer   | ------> |   Buffer    | ------> |  Consumer   |

| SC\_THREAD   |         | Passive Ch. |         | SC\_THREAD   |

+-------------+         +-------------+         +-------------+



&#x20;    sc\_port            sc\_export            sc\_port

