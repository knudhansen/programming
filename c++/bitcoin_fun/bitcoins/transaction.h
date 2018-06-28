typedef (uint8*) transactionReference_t;
typedef (uint8*) signature_t;

class Transaction;

class Input {
 private:
  transactionReference_t *reference;
 public:
  Input(transactionReference_t *reference);
  Transaction* getTransaction(void);
}

class Output {
 private:
  transactionDestination_t *destination;
 public:
  Output(transactionDestination_t destination);
}

class Transaction {
 private:
  Input *inputs;
  Output *outputs;
  signature_t signature;
 public:
  Transaction(void);
  void addInput(Input *input);
  void addOutput(Output *output);
  void sign(privateKey_t *privateKey); 
  transactionReference_t getReference(void);
  bool validate(void);
}
