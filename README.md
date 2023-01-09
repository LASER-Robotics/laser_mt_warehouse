<h1>L1LMR (Laser Logistic Multi Robots)</h1>

<h1>Arquitetura do robô</h1>

<p>O robô é composto por um drone e um robô terrestre atuando como uma base de pouso móvel, ao drone esta acoplado uma câmera para o processamento dos códigos de barras da warehouse</p>

<h1>Setup</h1>

<p>Como utilizamos o turtlebot 2 como nosso robô móvel precisamos utilizar como sistema operacional o ubuntu 16 pois a distribuição do ROS compativel com o turtlebot 2 é a kinetic</p>

<p>Após instalar o sistema operacional crie um ambiente virtual de trabalho python para que você possa instalar as dependências para executar o projeto, depois de criar o ambiente e estiver com ele ativado siga os passos abaixo:</p>

<ol>
    <li>execute a seguinte linha de comando no terminal</li>
</ol>

<h1>Como montar e lançar o L1LMR?</h1>

<h2>Câmera</h2>

<p>Comecaremos configurando a camera acoplada ao drone. Como o nosso drone nao tinha uma câmera colocamos um modúlo ESP-CAM para ser a nossa câmera.</p>

<h3>ESP-CAM</h3>

<p>Para compilar o código para o módulo ESP-CAM é preciso usar um módulo FTDI pois a ESP-CAM não possui entrada micro usb, através do módulo FTDI o código é passado através de comunicação serial.</p>

<p>Ao montar o esquemático mostrado na figura vocês está pronto para compilar o código da câmera para o módulo ESP-CAM, o arquivo a ser compilado é o arquivo <a href="">Embedded_esp_cam.ino</a>.</p>

<h3>Servidor socket</h3>

<p>Como nosso drone não possui desempenho suficiente para processar os códigos de barras a maneira de solucionar esse problema foi fazer o processamento externamente em outro computador.</p>

<p>O módulo ESP-CAM publica as imagens capturadas no servidor socket e o servidor recolhe as imagens salva e as processas, salvamos porquê ao fim poderemos montar um video da visão do drone</p>

<p>Para iniciar o server de processamento das imagens execute o script <a href="">API_image_processing_L1LMR1.py</a> depois é só ligar o módulo ESP_CAM e esperar as imagens começarem a ser salva e processadas.</p>
