import os.path
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../..'))

import specs.stdapi as stdapi
from wrappers.trace import Tracer



class Tracer_Optim(Tracer):
    def __init__(self):
        super().__init__()


    def traceFunctionImplBody(self, function):
        if not function.internal:
            print('    unsigned _call = trace::localWriter.beginEnter(&_%s_sig);' % (function.name,))
            for arg in function.args:
                if not arg.output:
                    self.serializeArg(function, arg)
            print('    trace::localWriter.endEnter();')
        #self.invokeFunction(function)
        if not function.internal:
            print('    trace::localWriter.beginLeave(_call);')
            print('    if (%s) {' % self.wasFunctionSuccessful(function))
            for arg in function.args:
                if arg.output:
                    self.serializeArg(function, arg)
                    self.wrapArg(function, arg)
            print('    }')
            if function.type is not stdapi.Void:
                self.serializeRet(function, "_result")
            if function.type is not stdapi.Void:
                self.wrapRet(function, "_result")
            print('    trace::localWriter.endLeave();')

    