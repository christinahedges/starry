# -*- coding: utf-8 -*-
from __future__ import division, print_function
import numpy as np
from theano import gof
import theano.tensor as tt
import theano.sparse as ts

__all__ = ["dotRxy", "dotRxyT"]


class dotRxy(tt.Op):

    def __init__(self, c_ops):
        self.c_ops = c_ops
        self._grad_op = dotRxyGradient(self)

    def make_node(self, *inputs):
        inputs = [tt.as_tensor_variable(i) for i in inputs]
        outputs = [tt.TensorType(inputs[0].dtype, (False, False))()]
        return gof.Apply(self, inputs, outputs)

    def infer_shape(self, node, shapes):
        return shapes[0],

    def R_op(self, inputs, eval_points):
        if eval_points[0] is None:
            return eval_points
        return self.grad(inputs, eval_points)

    def perform(self, node, inputs, outputs):
        outputs[0][0] = self.c_ops.dotRxy(*inputs)

    def grad(self, inputs, gradients):
        return self._grad_op(*(inputs + gradients))


class dotRxyGradient(tt.Op):

    def __init__(self, base_op):
        self.base_op = base_op

    def make_node(self, *inputs):
        inputs = [tt.as_tensor_variable(i) for i in inputs]
        outputs = [i.type() for i in inputs[:-1]]
        return gof.Apply(self, inputs, outputs)

    def infer_shape(self, node, shapes):
        return shapes[:-1]

    def perform(self, node, inputs, outputs):
        bM, binc, bobl = self.base_op.c_ops.dotRxy(*inputs)
        outputs[0][0] = np.reshape(bM, np.shape(inputs[0]))
        outputs[1][0] = np.reshape(binc, np.shape(inputs[1]))
        outputs[2][0] = np.reshape(bobl, np.shape(inputs[2]))


class dotRxyT(tt.Op):

    def __init__(self, c_ops):
        self.c_ops = c_ops
        self._grad_op = dotRxyTGradient(self)

    def make_node(self, *inputs):
        inputs = [tt.as_tensor_variable(i) for i in inputs]
        outputs = [tt.TensorType(inputs[0].dtype, (False, False))()]
        return gof.Apply(self, inputs, outputs)

    def infer_shape(self, node, shapes):
        return shapes[0],

    def R_op(self, inputs, eval_points):
        if eval_points[0] is None:
            return eval_points
        return self.grad(inputs, eval_points)

    def perform(self, node, inputs, outputs):
        outputs[0][0] = self.c_ops.dotRxyT(*inputs)

    def grad(self, inputs, gradients):
        return self._grad_op(*(inputs + gradients))


class dotRxyTGradient(tt.Op):

    def __init__(self, base_op):
        self.base_op = base_op

    def make_node(self, *inputs):
        inputs = [tt.as_tensor_variable(i) for i in inputs]
        outputs = [i.type() for i in inputs[:-1]]
        return gof.Apply(self, inputs, outputs)

    def infer_shape(self, node, shapes):
        return shapes[:-1]

    def perform(self, node, inputs, outputs):
        bM, binc, bobl = self.base_op.c_ops.dotRxyT(*inputs)
        outputs[0][0] = np.reshape(bM, np.shape(inputs[0]))
        outputs[1][0] = np.reshape(binc, np.shape(inputs[1]))
        outputs[2][0] = np.reshape(bobl, np.shape(inputs[2]))