import torch

class FlattenTrans:
    def __call__(self, x):
        return x.view(-1)