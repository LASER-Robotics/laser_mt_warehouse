<h1>L1LMR (Laser Logistic Multi Robots)</h1>

<h1>Arquitetura do robô</h1>

<p>O robô é composto por um drone e um robô terrestre atuando como uma base de pouso móvel, ao drone esta acoplado uma câmera para o processamento dos códigos de barras da warehouse.</p>

<h1>Setup</h1>

<p>Como utilizamos o turtlebot 2 como nosso robô móvel precisamos utilizar como sistema operacional o ubuntu 16 pois a distribuição do ROS compativel com o turtlebot 2 é a kinetic.</p>

<p>Após instalar o sistema operacional crie um ambiente virtual de trabalho python para que você possa instalar as dependências para executar o projeto, depois de criar o ambiente e estiver com ele ativado execute a seguinte linha de comando no terminal para instalar as dependências do projeto:</p>

```
    pip install -r requirements. txt
```

<h1>Como montar e lançar o L1LMR?</h1>

<h2>Câmera</h2>

<p>Comecaremos configurando a camera acoplada ao drone. Como o nosso drone nao tinha uma câmera colocamos um modúlo ESP-CAM para ser a nossa câmera.</p>

<h3>ESP-CAM</h3>

<p>Para compilar o código para o módulo ESP-CAM é preciso usar um módulo FTDI pois a ESP-CAM não possui entrada micro usb, através do módulo FTDI o código é passado através de comunicação serial.</p>

<img src="">

<p>Ao montar o esquemático mostrado na figura vocês está pronto para compilar o código da câmera para o módulo ESP-CAM, o arquivo a ser compilado é o arquivo <a href="">Embedded_esp_cam.ino</a>.</p>

<h3>Servidor socket</h3>

<p>Como nosso drone não possui desempenho suficiente para processar os códigos de barras a maneira de solucionar esse problema foi fazer o processamento externamente em outro computador.</p>

<p>O módulo ESP-CAM publica as imagens capturadas no servidor socket e o servidor recolhe as imagens salva e as processas, salvamos porquê ao fim poderemos montar um video da visão do drone.</p>

<p>Para iniciar o server de processamento das imagens execute o script <a href="">API_image_processing_L1LMR1.py</a> depois é só ligar o módulo ESP-CAM e esperar as imagens começarem a ser salva e processadas.</p>

<h2>Drone</h2>

<p>O drone que utilizamos foi o mambo da marca Parrot, para controlar o drone é utilizado a biblioteca pyparrot, através da bilbioteca é possivel mandar comandos pré-programados para o mambo.</p>

<p>Nenhum código é embarcado no drone pois ele é um dispositivo "caixa preta" a biblioteca atua como um protocolo de comunicação entre o drone e o script em python.</p>

<p>A comunição com o drone pode ser feita através do BLE (bluetooth low energy) ou por WiFi, foi utilizado a comunicação por BLE. Para isso precisamos saber o endereço bluetooth do mambo siga os passos abaixos para conseguir o endereço do mambo.</p>

<ol>
    <li>Ligue o drone.</li>
    <li>Abra um terminal e navegue até a pasta do seu ambiente virtual.</li>
    <li>execute o seguinte comando no seu terminal:</li> 
    ```
        sudo python lib/python3.10/site-packages/pyparrot/scripts/findMinidrone.py
    ```
    <li>Espere o script terminar de buscar o endereço do drone e depois salve-o.</li>
</ol>

