rem use boost 1.73
rem you must manually open vs command line tool to run it
b2 install --prefix=".\BoostLib"  address-model=64 link=static runtime-link=static threading=multi architecture=x86 toolset=msvc-14.1 --build-type=complete
pause