[![CodeFactor](https://www.codefactor.io/repository/github/graphene-dev/graphenechain/badge/master)](https://www.codefactor.io/repository/github/graphene-dev/graphenechain/overview/master)
[![](https://tokei.rs/b1/github/Graphene-Dev/GrapheneChain?category=lines)](https://github.com/Graphene-Dev/GrapheneChain)
[![](https://tokei.rs/b1/github/Graphene-Dev/GrapheneChain?category=files)](https://github.com/Graphene-Dev/GrapheneChain)

# GrapheneChain
GrapheneChain is a template cryptocurrency chain 
developed for those who want to run a crypto 
or learn about cryptocurrencies, 
but may not have the time or skills 
to create a custom cryptocurrency from scratch.

# Compiling:
* Windows 10
    - From the start menu, open 'x64 Native Tools Command Prompt for vs2019'.
    - `cd <your_Graphene_directory>`
    - `mkdir build`
    - `cd build`
    - `cmake -G "Visual Studio 16 2019" -A x64 ..`
    - `MSBuild GrapheneChain.sln`
    The binaries will be in `Debug` folder when it is done
      