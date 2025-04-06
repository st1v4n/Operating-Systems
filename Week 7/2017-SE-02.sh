 #!/bin/bash
  
   if [[ "${#}" -ne 3 ]] ; then
      echo "Invalid number of arguments" >&2
      exit 1
   fi
   if [[ ! -d "${1}" || ! -d "${2}" ]] ; then
      echo "not a dir" >&2
      exit 2
  fi
  if [[ "$(whoami)" != root ]] ; then
     exit 0
  fi
 
  while read file ; do
      dst=$(echo "${file}" | sed -E "s/${1}(.*)/${2}\1/")
      dirName=$(dirName "${dst}")
      #fileReal="$(realpath ${dirName})"
      mkdir -p "${dirname}"
      mv ${file} ${dst}
  done < <(find "${1}" -type f -name "*${3}*" 2>/dev/null)
