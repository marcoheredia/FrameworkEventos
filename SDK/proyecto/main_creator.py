import os

main = open("./main/main.c", "w")
for modulename in os.listdir('./components/'):
	if modulename!='fw':
		if 'void '+ modulename +'_init()' in open('./components/'+ modulename +'/src/'+ modulename +'.c').read():
			main.write("#include \"../components/"+modulename+"/include/"+modulename+".h\"" + os.linesep)

main.write(os.linesep + "void app_main(void)" + os.linesep )
main.write("{" + os.linesep )	
		
for modulename in os.listdir('./components/'):
	if modulename!='fw':
		if 'void '+ modulename +'_init()' in open('./components/'+ modulename +'/src/'+ modulename +'.c').read():
			main.write("\t"+modulename+"_init();" + os.linesep )

main.write("}" + os.linesep )
main.close()