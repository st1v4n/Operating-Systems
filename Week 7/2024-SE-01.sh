#!/bin/bash
  
   files="$(mktemp)"
   words="$(mktemp)"
   for arg in "${@}" ; do
       if echo "${arg}" | grep -q -E "-R[A-Za-z0-9]+=[A-Za-z0-9]+" ; then
           echo "${arg}" | sed -e "s/^-R(.*)/\1/" >>"${words}"
       else
           if [[ ! -f "${arg} " ]] ; then
              exit 11
          else
              echo "${arg}" >>"${files}"
          fi
      fi
  done
  pwgens="$(mktemp)"
  while read file ; do
      while read word ; do
          first="$(echo "${word}" | cut -d '=' -f 1)"
          second="$(echo "${word}" | cut -d '=' -f 2)"
          pw="$(pwgen)"
          sed -i -E "s/(\b)${first}(\b)/\1${pw}${second}\2/g" "${file}"
          echo "${pw}${second}=${second}" >> "${pwgens}"
      done< "${words}"
  done< "${files}"
 
  while read file ; do
      while read word ; do
          first="$(echo "${word}" | cut -d '=' -f 1)"
          second="$(echo "${word}" | cut -d '=' -f 2)"
          sed -i -E "s/(\b)${first}(\b)/\1${second}\2/g" "${file}"
      done< "${pwgens}"
  done< "${files}"
 
  rm "${pwgens}"
  rm "${files}"
  rm "${words}"
