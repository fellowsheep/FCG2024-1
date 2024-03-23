# Configurando projetos em C++ com OpenGL no Visual Studio Code
## Um mini-tutorial

### Algumas considerações
- Este passo-a-passo foi feito utilizando Sistema Operacional Windows (10, 11), configuração da IDE C++ no Visual Studio Code(https://code.visualstudio.com/download) e utilizando o compilador MinGW, via MSys2 - https://www.msys2.org/).

## Adicionando suporte à linguagem C++ no Visual Studio Code

1 - Baixar o VS Code: https://code.visualstudio.com/download

2 - Baixar extensão C++: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

3 - Escolher qual compilador C++ baixar: MSVC (Microsoft, o mesmo do Visual Studio) ou MinGW (open source): https://code.visualstudio.com/docs/languages/cpp

 - Se estiver usando o Windows e escolher o MinGW:
   - Baixar e instalar o MSys2: https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe 
   - No terminal do MSys2, digitar:
     
    `pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain`


4 - Se estiver em um computador que não tenha acesso de adm, adicionar temporariamente ao path com este comando (via terminal): 

   `set PATH=%PATH%;C:\msys64\ucrt64\bin` 
     
5 - Realizados estes passos, entre no Visual Studio Code, entre em uma pasta (ou crie uma), e crie o seguinte arquivo de código em C++:
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    cout << "Teste" << endl;
    return 0;
}
```
