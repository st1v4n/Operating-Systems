 #!/bin/bash
  
   if [[ "${#}" -ne 2 && "${#}" -ne 1 ]] ; then
       echo "Invalid number of arguments!" >&2
       exit 1
   fi
   if [[ ! -d "${1}" ]] ; then
      echo "First argument should be a directory!" >&2
       exit 2
  fi
  if [[ "${#}" -eq 2 ]] ; then
      count="${2}"
      echo "$(find "${1}" -type f -links +$((count-1)))"
  else
      broken_count="0"
      while read symlink ; do
          if [[ ! -e "${symlink}" ]] ; then
              broken_count=$((broken_count+1))
          fi
          echo "Broken symlinks: "${broken_count}""
      done< <(find "${1}" -type l 2>/dev/null)
  fi
