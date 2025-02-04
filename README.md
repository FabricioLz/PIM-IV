# Resumo do Projeto - PIM IV (ADS)

## 📌 Informações Gerais
- **Universidade:** UNIP EaD  
- **Curso:** Análise e Desenvolvimento de Sistemas  
- **Autores:**  
  - Ana Paula Melo Chinko  
  - Fabricio Luiz Rocha  
  - Kamila de Souza Saraiva  
  - Maria Eduarda da Silva  
  - Maxwel Marinho de Andrade  
  - Thomas Andrade Albano  
- **Orientador(a):** Prof. Me. Karhyne Assis  
- **Ano:** 2024  

---

## 🖥️ Objetivo do Projeto
Desenvolver um software em **linguagem C** para gerenciar **cadastros e relatórios** de uma **startup de soluções ambientais**.

---

## 🔑 Principais Funcionalidades
- **Cadastro de Usuário com criptografia**
- **Login Seguro**  
- **Cadastro de Empresas**  
- **Registro de Resíduos e Custos Mensais**  
- **Geração de Relatórios** em diferentes formatos (TXT, CSV, XLS)  

---

## 🔍 Tecnologias Utilizadas
- **Linguagem C**
- **Compilador:** GCC (GNU Compiler Collection)  
- **IDE:** Code::Blocks  
- **Modelo de Desenvolvimento:** RAD (Rapid Application Development)  
- **Criptografia Simples** para senhas  
- **LGPD:** Implementação de segurança de dados  

---

## 📑 Estrutura do Código
- **Uso de Structs:**  
  - `User` → Nome e senha criptografada  
  - `Company` → Dados da empresa, resíduos e custos  
- **Funções Principais:**  
  - Atualização de Resíduos e Custos
O sistema solicita o CNPJ da empresa.
Caso a empresa exista, solicita:
O mês (1-12).
A quantidade de resíduos tratados (em toneladas).
O custo estimado (em R$).
Esses valores são armazenados para uso nos `relatórios` e `decryptPassword()`  
  - `registerUser()` e `login()`  
  - `registerCompany()` e `updateWasteAndCosts()`  
  - `generateReports()`  

---

## 📊 Relatórios Gerados
- **Resumo de resíduos tratados e custos mensais**  
- **Relatórios semestrais de tratamento de resíduos**  
- **Gastos financeiros por empresa**  
- **Identificação de empresas com menor produção**  
- **Aporte financeiro semestral**  
- **O sistema pode gerar relatórios ambientais nos formatos:**
- **📂 TXT (relatorio_ambiental.txt)**
- **📊 CSV (relatorio_ambiental.csv)**
- **📋 XLS (relatorio_ambiental.xls)**

---

## 🛠️ Processo de Desenvolvimento
1. **Definição de requisitos**  
2. **Divisão do sistema em módulos**  
3. **Implementação e testes individuais**  
4. **Integração dos módulos**  
5. **Testes gerais e ajustes**  
6. **Geração e validação de relatórios**  

---

## ✅ Conclusão
- O software **automatiza o gerenciamento de dados ambientais**  
- **Facilita a geração de relatórios para as indústrias**  
- **Garante a proteção de dados conforme a LGPD**  
- **Possibilidade de expansão futura do sistema**  

