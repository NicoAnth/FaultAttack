# Fault Attack against DES

A Differential Fault Attack against last round of DES.

## Installation

Simply use make command to compile.

```bash
make
```

## Usage

Hardcode your correct and your faulty ciphers in FaultAttack.cpp, faultAttack16() function. Then run the program, it will return the key associate to your cipher. 

```cpp
std::string correctCypher = "144FED14635AFD89";
std::vector<std::string> FaultCyphers = {"164EED50635AFD8D","144DED50635BFD89","145FEF50635AFD89","151FE956735AFD89","151FED54715BFD89","150FE9147358FD89","154FED14735AFF89","140FE915234EFD8B",
    "1C4FE915335AFD89","1447ED15234AFD89","144FE515235EFD89","544FFD1C234AFD89","544FFD156B4AFD89","544FED146312FD88","544FFD14631AF589","144FFD14671AED80","744FFD14671AFCC8","146FED14675AFC89",
    "144FCD14635AECC9","004FEC34635AEC89","104FEC14435AECC9","004FAD14637AFD89","104FAC14635ADD89","044FAC14635AB9A9","804FED14625ABD89","14CFED04625AF989","144F6D14635AB989","144AED84635AB989",
    "144EED04E25AFD8D","144BED1463DAFD8D","144FED14635A7D9D","144AED54635BFD0D"};
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
