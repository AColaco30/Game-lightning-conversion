// Trabalho realizado por: André Filipe Costa Colaço.
// UC: 2020220301.


bool lastState = LOW;       // Leitura anterior do botão
bool bttState;              // Leitura atual do botão
long debounceDelay = 50;    // Tempo do debounce
long bounce;                // Ultimo instante em que o botão mudou de estado
long tempo = 15000;         // Tempo limite para selecionar o número
long reset = 1000;          // Tempo para resetar
bool start = true;          // Começa o jogo
int count = 0;              // Conta o número de vezes
int x;                      // Número gerado aleatoriamente

void setup() {
  
  // Inicializa os 5 leds, nos pinos 6, 7, 8, 9 e 10, através de um ciclo:
  for (int p = 6; p < 11; p++) {
    pinMode(p, OUTPUT);
  }
  // Configura o botão no pino 5:
  pinMode(5, INPUT_PULLUP);
  // Faz com que os números gerados sejam aleatorios:
  randomSeed(analogRead(0));
  Serial.begin(9600);

}


void loop() {

  // Quando start for true o jogo recomeça:
  if (start == true) {
    Serial.println("Tens 15 segundos para acertar no numero!");
    // Escolhe um número aleatório:
    x = random(1, 32);
    gerarbinario();
    // Para o jogo nao estar constantemente a gerar números:
    start = false;
    // Para o jogo não estar constantemente a acabar:
    bounce = millis();
    // Volta a por a contagem a zero:
    count = 0;
  }

  resultado();

  debounce();

}


// Passa o número gerado para binário acendendo os leds:
void gerarbinario() {

  // Se o último bit for 1 acende o led no pino 10 e se for 0 não acende:
  if (x & 0b1 == 1) {
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(10, LOW);
  }

  // Faz um shift para a direita e se o ultimo bit for 1 o led no pino 9 acende e se for 0 não acende:
  if ((x >> 1) & 0b1 == 1) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }

  // Faz dois shift´s para a direita e se o ultimo bit for 1 o led no pino 8 acende e se for 0 não acende:
  if ((x >> 2) & 0b1 == 1) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  // Faz três shift´s para a direita e se o ultimo bit for 1 o led no pino 7 acende e se for 0 não acende:
  if ((x >> 3) & 0b1 == 1) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }

  // Faz quatro shift´s para a direita e se o ultimo bit for 1 o led no pino 6 acende e se for 0 não acende:
  if ((x >> 4) & 0b1 == 1) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  
}


// Diz-nos se acertou no número ou não:
void resultado() {
  
  // Se passarem os 15 segundos:
  if (millis() - bounce > tempo) {
    // Se o valor que estiver na variável count for igual ao número gerado,
    // Então imprime uma mensagem de parabéns:
    if (count == x) {
      Serial.println("Parabens! Acertas-te no numero.");
      // Apaga todos os leds e acende-os de forma sequencial,
      // Do bit menos significativo para o mais significativo:
      for (int p = 10; p > 5; p--) {
        digitalWrite(p, LOW);
      }
      delay(100);
      for (int p = 10; p > 5; p--) {
        digitalWrite(p, HIGH);
        delay(500);
      }
    }

    // Caso o valor nao seja igual,
    // Imprime uma mensagem a dizer qual era o número gerado:
    else {
      Serial.print("Erraste! O número era ");
      Serial.println(x);
      delay(1500);
    }
    // Recomeça o jogo:
    start = true;
  }
  
}


// Quando o botão é premido, o valor devolvido vai alternando de LOW para HIGH e HIGH para LOW
// Ou seja, o debounce faz com que isso não aconteca:
void debounce() {

  // Lê o estado do botão:
  int btt = !(digitalRead(5));

  // Se o estado mudar:
  if (btt != lastState) {
    // Reseta o tempo do debounce
    // A função millis devolve o tempo, em milissegundos, decorrido desde o momento em que o arduino foi ligado:
    bounce = millis();
  }

  // Se tiver passado 50 milissegundos desde a ultima vez que o botão foi premido:
  if ((millis() - bounce) > debounceDelay) {
    // Se o estado mudar:
    if (btt != bttState) {
      // O estado anterior do botão passa a ser o atual:
      bttState = btt;

      // Se o estado do botão for HIGH:
      if (bttState == HIGH) {
        // O contador vai incrementando 1:
        count = count + 1;
        // Caso o contador chegue ao 32, então este volta a 1:
        if (count == 32) {
          count = 1;
        }
        Serial.println(count);
      }
    }

    // Reset
    // Caso o botão seja premido durante 1 segundo:
    if ((millis() - bounce > reset) && (bttState == HIGH)) {
      // Recomeça o jogo:
      start = true;
      // Reseta o tempo do debounce:
      bounce = millis();
    }

  }
  // Guarda a leitura deste loop para o próximo:
  lastState = btt;

}
