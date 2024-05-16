#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <csignal>
#include <functional>
#include <iostream>

using namespace std;

class SignalHandler {
public:
    static void setupSignalHandler(function<void(int)> handler) {
        signalHandlerFunction = handler;
        signal(SIGINT, SignalHandler::handleSignal);
    }

private:
    static function<void(int)> signalHandlerFunction;

    static void handleSignal(int signum) {
        if (signalHandlerFunction) {
            signalHandlerFunction(signum);
        }
    }
};

function<void(int)> SignalHandler::signalHandlerFunction = nullptr;

#endif 
