#!/usr/bin/env python
# vim: tabstop=2 expandtab bs=2 shiftwidth=2 ai cin smarttab

import argparse
import collections
import json
import os
import sys

parser = argparse.ArgumentParser(description='Create C config file and header from a JSON config definition')
parser.add_argument('--c_file', required=True, help="name of output file")
parser.add_argument('--c_const_char', type=bool, default=False, help="Generate const char members for strings")
parser.add_argument('--dest_dir', default=".", help="base path of generated files")
parser.add_argument('json', nargs='+', help="JSON config definition files")
src_body = ""
     
def do(obj, first_file, path, hdr):
  global src_body
  level = len(path) - 1
  indent = '  ' * level
  json_indent = '  ' * (level + 1)
  name = path[-1]
  # Start structure definition
  if level > 0:
    hdr.append(indent + 'struct ' + '_'.join(path) + ' {')
  first_key = True
  fw_i=1
  for k, v in obj.iteritems():
    key = '.'.join(path[1:] + [k])
    fw_name.append(k)
    fw_struc.append(key)
    comma = ',' if (not first_key) or (level == 0 and not first_file) else ''
    if isinstance(v, dict):
      fw_type.append('FW_TYPE_OBJECT')
      src_body=src_body+  "{comma}\n{indent}" .format(comma=comma, indent=json_indent)+"{"
      do(v, first_file, path + [k], hdr)
    elif isinstance(v, list):
      raise ValueError('Arrays are not supported')
    else:
      if isinstance(v, basestring):
        c_type = 'const char *' if args.c_const_char else 'char *'
      elif isinstance(v, float):
        c_type = 'float '
      else:
        c_type = 'int '
      hdr.append(indent + '  ' + c_type + k + ';')
      prefix = comma + "\n" + json_indent
      if isinstance(v, basestring):
        fw_type.append('char *')
        src_body=src_body+'{p}"{k}"'.format(p=prefix, k=obj[k])
      elif isinstance(v, bool):
        fw_type.append('bool ')
        if(obj[k]==True):
          src_body=src_body+"{p}true".format(p=prefix)
        else:
          src_body=src_body+"{p}false".format(p=prefix)
      elif isinstance(v, float):
        fw_type.append('float ')
        src_body=src_body+"{p}{k}".format(p=prefix, k=obj[k])
      else:
        fw_type.append('int ')
        src_body=src_body+"{p}{k}".format(p=prefix, k=obj[k])



    first_key = False
  if level > 0:
    hdr.append(indent + '} %s;' % name)
    src_body=src_body+"\n"+indent + "}"


if __name__ == '__main__':
  args = parser.parse_args()
  origin = ' '.join(args.json)
  hdr = []
  fw_name, fw_struc, fw_type = [], [], []
  name = os.path.basename(args.c_file)
  src_body = src_body+'#include "{file}.h"\n\nstatic struct {file} config0='.format(file=args.c_file)+'{'
  first_file = True
  for json_file in args.json:
    if os.path.isdir(json_file):
      continue
    with open(json_file) as jf:
      obj = json.load(jf, object_pairs_hook=collections.OrderedDict)
      do(obj, first_file, [name], hdr)
    first_file = False
    src_body=src_body+'};\n'

  src_getters=""
  hdr_getters=""
  for i in range(len(fw_struc) ):
    if(fw_type[i]!='FW_TYPE_OBJECT'):
      src_getters=src_getters+'\n{type}get_{name}()'.format(type=fw_type[i],name=fw_struc[i].replace('.','_'))+'{\n'
      src_getters=src_getters+"\treturn config0.{name};".format(name=fw_struc[i])+"\n}\n"
      src_getters=src_getters+"\nvoid set_{name}({type}new_value)".format(type=fw_type[i],name=fw_struc[i].replace(".","_"))+"{\n"
      src_getters=src_getters+"\tconfig0.{name}=new_value;".format(name=fw_struc[i])+"\n}\n"
      hdr_getters=hdr_getters+"\n{type}get_{name}();\n".format(type=fw_type[i],name=fw_struc[i].replace(".","_"))
      hdr_getters=hdr_getters+"\nvoid set_{name}({type}new_value);\n".format(type=fw_type[i],name=fw_struc[i].replace(".","_"))

  hdr.insert(0, '''\
/* generated from {origin} - do not edit */
#ifndef {name_uc}_H_
#define {name_uc}_H_
#include <stddef.h>
#include <stdbool.h>


struct {name} {{\
'''.format(name=name, name_uc=name.upper(), origin=origin))
  hdr.append('''\
}};

{getters}
#endif /* {name_uc}_H_ */

'''.format(name=name, name_uc=name.upper(),getters=hdr_getters))

open(os.path.join(args.dest_dir, name + '.h'), 'w+').write('\n'.join(hdr))

open(os.path.join(args.dest_dir, name + '.c'), 'w').write(src_body+src_getters)
