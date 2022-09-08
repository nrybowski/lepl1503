
import random
from statistics import median
import math
base_1={
    "nb_students" : 10,
    "code" : 1101,
    "average_grade" : 50,
    "median_grade" :  50,
    "max_grade" : 0,
    "min_grade" : 100,
    "unsorted_data" : {},
    "sorted_data" : {}
}

base_2={
    "nb_students" : 1000,
    "code" : 1103,
    "average_grade" : 50,
    "median_grade" :  50,
    "max_grade" : 0,
    "min_grade" : 100,
    "unsorted_data" : {},
    "sorted_data" : {}
}

base_3={
    "nb_students" : 10000,
    "code" : 1503,
    "average_grade" : 50,
    "median_grade" :  50,
    "max_grade" : 0,
    "min_grade" : 100,
    "unsorted_data" : {},
    "sorted_data" : {}
}

def make_student_base(dict):
    nb = dict["nb_students"]
    for i in range(nb):
        base =  i #ça va les perturber car faudra faire -39002000 dans la fonction compare - à réflechir 39002000 + i*(10**4)
        grade = random.randint(0, 100)
        if grade>dict["max_grade"]: dict["max_grade"]=grade
        if grade<dict["min_grade"]: dict["min_grade"]=grade
        dict["unsorted_data"][base]= grade
    dict["sorted_data"] = {k: v for k, v in sorted(dict["unsorted_data"].items(), key=lambda item: item[1],reverse=True)}
    dict["average_grade"] = sum(dict["sorted_data"].values()) // nb
    dict["median_grade"] = math.floor(median(dict["sorted_data"].values()))
    

def make_binary_file(file_name,data,sorted):
    """
    @pre : 
        file_name : le nom du fichier de sortie binaire
        data : un dictionnaire contenant les informations sur la base de donnée : 
            nombre d'étudiants, code du cours, moyenne, médianne, note max, note min, 
            un dictionnaire contenant les (nomas,note) non triés : unsorted_data
            un dictionnaire contenant les tuples triés : sorted_data
        sorted : booléan : 
            si sorted = 1 : génère le fichier qui sera donné aux étudiants (input_file)
            si sorted !=1 : génère le fichier de réponse (liste des nomas triés)


    """
    file = open(file_name, "wb")
    if (sorted ==1):
        file.write(data["nb_students"].to_bytes(4, 'big'))
        file.write(data["code"].to_bytes(2, 'big'))
        file.write(data["average_grade"].to_bytes(1, 'big'))
        file.write(data["median_grade"].to_bytes(1, 'big'))
        file.write(data["max_grade"].to_bytes(1, 'big'))
        file.write(data["min_grade"].to_bytes(1, 'big'))

        for grade in data["unsorted_data"].values():
            file.write(grade.to_bytes(1,'big'))
        #print(data["unsorted_data"].values())
        for noma in data["unsorted_data"].keys():
            file.write(int(noma).to_bytes(4,'big'))
        #print(data["unsorted_data"].keys())

    else:
        for noma in data["sorted_data"].keys():
            file.write(noma.to_bytes(4,'big'))
        #print(data["sorted_data"].keys())

    file.close()




if __name__ == "__main__":
    base_list = [base_1,base_2,base_3]
    for base in base_list:
        make_student_base(base)
        input = "input/" + str(base["code"]) +".bin"
        output = "expected_output/"+str(base["code"]) +".bin"
        make_binary_file(input,base,1)
        make_binary_file(output,base,0)

    


