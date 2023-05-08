import pandas as pd
import matplotlib.pyplot as plt

# Lê o arquivo CSV
df = pd.read_csv("dados.csv")

# Seleciona as colunas desejadas
x = df["tam"]
y1 = df["elastic_FP"]
y2 = df['elastic_heap']

# Plota o gráfico
plt.subplot(2,1,1)
plt.scatter(x, y1)
plt.xlabel("Tamanho")
plt.ylabel("Interações")
plt.title("Enqueue Fila de Prioridade")
plt.show()
plt.subplot(1,2,2)
plt.scatter(x, y2)
plt.xlabel("Tamanho")
plt.ylabel("Interações")
plt.title("Enqueue HEAP")
plt.show()