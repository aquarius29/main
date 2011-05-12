typedef struct manualCommand {
    int value;
    struct manualCommand *next;
} manualCommand;

void initManualCommandsList(void);
void receiveManualMovementCommand(int command);
void freeManualCommandList(void);

// non static variables for testing
// manualCommand *first;
// manualCommand *last;