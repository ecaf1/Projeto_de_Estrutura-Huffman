import pandas as pd
import matplotlib.pyplot as plt

# Lê o arquivo CSV
df = pd.read_csv("dados.csv")

# Seleciona as colunas desejadas
x = df["tam"]
y = df["elastic_FP"]

# Plota o gráfico
plt.scatter(x, y)
plt.xlabel("Tamanho")
plt.ylabel("Elasticidade FP")
plt.title("Gráfico de Elasticidade FP x Tamanho")
plt.show()