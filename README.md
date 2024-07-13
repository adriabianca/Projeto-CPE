# Projeto-CPE
Projeto computacional da matéria de Computação para Engenharia da UnB

Para compilar o programa no VSCode será necessário ter instalado as ferramentas *vcpkg*, para fazer download de bibliotecas, no caso o *raylib*, *CMake*, o gerenciador de build do projeto, e o generator *Visual Studio 17 2022*(Windows) ou *Unix Makefiles*(Mac), para gerar os arquivos iniciais de build.

Caso esteja usando Windows, existe uma alternativa menos trabalhosa, que é baixando e instalando o pacote *raylib* do site oficial da biblioteca. Fazendo isso, o ambiente já vem todo configurado para rodar o programa.

Para configurar o CMake, será necessário alterar os arquivos _CMakePresets.json_ e _CmakeLists.txt_ para que seja compatível com as localizações dos arquivos na sua máquina.

Links relevantes:

* Tutorial CMake no VSCode: https://youtu.be/_BWU5mWqVA4?si=rIVuX2FPLibPX_yg
* Instalação e tutorial _quick start_ do vcpkg: https://github.com/microsoft/vcpkg
* Tutorial Configuração VSCode: https://visitlab.pages.fi.muni.cz/tutorials/vs-code/index.html
* Site do Raylib: https://www.raylib.com/index.html
* Tutorial download e instalação do Raylib fornecido no site oficial: https://youtu.be/PPrY54Evkx8?si=pQdeQp30eO0h7Zdj
