const transportadora1 = () => {
  pin_C10 = 1; //////////encender cinta transportador

  while (objeto < 6) {
    const sensor = false; /// valor de entrada, sensor de proximidad - en primera instancia es FALSE (0)

    if (sensor) {
      objeto++;
      /// muestras en pantalla el valor de objeto
    }
  }
  pin_C10 = 0; //////////apagas cinta transportadora
};

const transportadora2 = () => {
  const sensor = false; /// valor de entrada, sensor de proximidad - en primera instancia es FALSE (0)
  do {
    pin_C7 = 1; //////////encender cinta transportadora
    sensor = false; /// valor de entrada, sensor de proximidad - se lee el valor cada vez que inicia el ciclo
  } while (!sensor);
  pin_C7 = 0; //////////apagar cinta transportadora
};

const ProgramaCompleto = () => {
  const proceso = 0;
  const button = 0;
  while (true) {
    /// recibo valor del boton
    if ((button = 1)) {
      const led = 1; /// enceder puerto donde esta el led
      transportadora2();
      transportadora1();
    }
    proceso++;
    /// muestras en pantalla proceso finalizado - proceso = 1
  }
};
