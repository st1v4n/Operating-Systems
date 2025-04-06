 #!/bin/bash
  
   if [[ "${#}" -ne 2 && "${#}" -ne 1 ]] ; then
       echo "err" >&2
       exit 1
   fi
   if [[ ! -d "${1}" ]] ; then
       echo "not a dir" >&2
       exit 2
  fi
 
  if [[ "${#}" -eq 2 && ! -f "${2}" ]] ; then
      echo "arg 2 not a file" >&2
      exit 3
  fi
 
  out="/dev/stdout"
 
  if [[ "${#}" -eq 2 ]] ; then
      out="${2}"
  fi
  count=0
  while read symlink ; do
      if [[ -e "${symlink}" ]] ; then
          echo "$(basename ${symlink}) -> $(readlink "${symlink}")" >>"${out}"
      else
          count=$((count+1))
      fi
  done< <(find "${1}" -type l 2>/dev/null)
 
  echo "Broken symlinks: ${count}" >>"${out}"
