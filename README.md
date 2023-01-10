<h1>L1LMR (Laser Logistic Multi Robots)</h1>

<h1>O Sistema</h1>

<p>O robô é composto por um drone e um robô terrestre atuando como uma base de pouso móvel, ao drone esta acoplado uma câmera para o processamento dos códigos de barras da warehouse.</p>

<h1>Setup</h1>

<p>Utilizou-se para o robô terrestre o Turtlebot 2, usando o Ubuntu 16.04 com a distribuição do <a href = "http://wiki.ros.org/kinetic/Installation/Ubuntu">ROS Kinetic </a>, mantendo a compatibilidade entre o robô e SO utilizado. Logo abaixo contém um passo a passo de como realizar a instalação do Turtlebot no Ubuntu: </p>

```
sudo apt install ros-kinetic-turtlebot*
mkdir catkin_ws/src
catkin init
OBS: Dentro da pasta src coloque os itens contido em Turtlebot2/packages 
catkin build    
```

<p>Após instalar o sistema operacional crie um ambiente virtual de trabalho python para que você possa instalar as dependências para executar o projeto, depois de criar o ambiente e estiver com ele ativado execute a seguinte linha de comando no terminal para instalar as dependências do projeto:</p>

```
pip install -r requirements.txt
```

<h1>Como configurar o L1LMR</h1>

<h2>Câmera</h2>

<p>Comecaremos configurando a camera acoplada ao drone. Como o nosso drone nao tinha uma câmera colocamos um modúlo ESP-CAM para ser a nossa câmera.</p>

<h3>ESP-CAM</h3>

<p>Para compilar o código para o módulo ESP-CAM é preciso usar um módulo FTDI pois a ESP-CAM não possui entrada micro usb, através do módulo FTDI o código é passado através de comunicação serial.</p>

<img src="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/imgs_for_README/Img_ESP_CAM_FTDI.jpeg">

<p>Ao montar o esquemático mostrado na figura vocês está pronto para compilar o código da câmera para o módulo ESP-CAM, o arquivo a ser compilado é o arquivo <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/Drone_camera/Embedded_esp_cam/src/Embedded_esp_cam.ino">Embedded_esp_cam.ino</a>, mas antes de compilar configure o IP do server e a porta de acesso.</p>

<p>Depois de compilar o código basta desconectar todos os fios e ligar apenas os fios de alimentação 5V e GND para que o módulo execute o código compilado.</p>

<h3>Servidor socket</h3>

<p>Como nosso drone não possui desempenho suficiente para processar os códigos de barras a maneira de solucionar esse problema foi fazer o processamento externamente em outro computador.</p>

<p>O módulo ESP-CAM publica as imagens capturadas no servidor socket e o servidor recolhe as imagens salva e as processas, salvamos porquê ao fim poderemos montar um video da visão do drone. Para salvarmos é necessário criar uma pasta e passar o PATH da pasta para o script do server <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/Drone_camera/Image_processing/src/API_image_processing_L1LMR1.py">API_image_processing_L1LMR1.py</a>.</p>

<p>Para iniciar o server de processamento das imagens execute o script <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/Drone_camera/Image_processing/src/API_image_processing_L1LMR1.py">API_image_processing_L1LMR1.py</a>, lembre de colocar o mesmo IP e porta usado na compilação da ESP-CAM. Depois é só ligar o módulo ESP-CAM e esperar as imagens começarem a ser salva e processadas.</p>

<h2>Drone</h2>

<p>O drone que utilizamos foi o mambo da marca Parrot, para controlar o drone é utilizado a biblioteca pyparrot, através da bilbioteca é possivel mandar comandos pré-programados para o mambo.</p>

<p>Nenhum código é embarcado no drone pois ele é um dispositivo "caixa preta" a biblioteca atua como um protocolo de comunicação entre o drone e o script em python.</p>

<p>A comunição com o drone pode ser feita através do BLE (bluetooth low energy) ou por WiFi, foi utilizado a comunicação por BLE. Para isso precisamos saber o endereço bluetooth do mambo siga os passos abaixos para conseguir o endereço do mambo.</p>

<ol>
    <li>Ligue o drone.</li>
    <li>Abra um terminal e navegue até a pasta do seu ambiente virtual.</li>
    <li>execute o seguinte comando no seu terminal: 
    sudo python lib/python3.10/site-packages/pyparrot/scripts/ findMinidrone.py.</li> 
    <li>Espere o script terminar de buscar o endereço do drone e depois salve-o em algum lugar.</li>
</ol>

<h2>Turtlebot 2</h2>

<li> Para a 1 interação é necessário mapear o local, no qual o turtlebot irá operar usando os seguintes comandos: </li>

```
roslaunch turtlebot_bringup minimal.launch 
roslaunch turtlebot_navigation gmapping_demo.launch
roslaunch turtlebot_rviz view_navigation.launch
```
<li> Ao finalizar é necessário salvar o arquivo do mapa utilizando o seguinte comando: </li>

```
rosrun map_server map_server mymap.yaml
```

<li> Após essas etapas é so rodar o comandos para a operação do turtlebot </li>

```
EXPORT TURTLEBOT_MAP_FILE="$(CAMINHO DO ARQUIVO)"
roslaunch turtlebot_bringup minimal.launch
roslaunch turtlebot_navigation amcl_demo.launch (espere a odometria)
roslaunch turtlebot_rviz view_navigation.launch
```

<h2>Controladora</h2>

<p>Por ultimo configure a controladora que vai fazer a união do robô aéreo e terrestre. Essa parte é bem rápida, abra o arquivo <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/L1LMR-1.py">L1LMR1.py</a> coloque o endereço bluetooth do drone como parâmetro na inicialização da classe Drone, depois coloque o ID do Turtlebot 2 dependendo de quantos L1LMR irá ser usado, e pronto a controladora está configurada.</p>

<h1>Como lançar o L1LMR</h1>

<p>Siga os próximos passos para que o L1LMR inicialize corretamente:</p>

<ol>
    <li>Posicione o Turtlebots 2 em sua posição inicial, e execute todos os launchers do ROS necessários.</li>
    <li>Ligue o Mambo e coloque-o em cima do Turtlebot 2.</li>
    <li>Ligue o server socket.</li>
    <li>Execute o script da controladora.</li>
</ol>

<p>Pronto o L1LMR estará funcionando.</p>

<h1>Como usar mais de um L1LMR</h1>

<ul>
    <li>Primeiro compile o <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/Drone_camera/Embedded_esp_cam/src/Embedded_esp_cam.ino">Embedded_esp_cam.ino</a> na ESP-CAM colocando uma nova porta para acesso da API de processamento.</li> 
    <li>Agora clone os seguintes arquivos <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/Drone_camera/Image_processing/src/API_image_processing_L1LMR1.py">API_image_processing_L1LMR1.py</a>, <a href="https://github.com/LASER-Robotics/Mambo-Turtle-Warehouse/blob/main/L1LMR-1.py">L1LMR1.py</a> enumerando o fim dos arquivos com o ID do novo L1LMR.</li> 
    <li>Depois coloque a porta usada pela ESP-CAM para acessar a API, no arquivo do server e coloque o PATH da pasta para armazenar as imagens do novo L1LMR.</li>
    <li>Siga os passos anteriores que ainda não foram feitos.</li>
</ul>
