#!/usr/bin/env bash
set -euo pipefail

# Kopyalanacak DLL listesi (gerekli olabilecekleriyle beraber)
dlls=(
  "sfml-graphics-2.dll"
  "sfml-window-2.dll"
  "sfml-system-2.dll"
  "sfml-network-2.dll"
  "openal32.dll"
  "libgcc_s_seh-1.dll"
  "libstdc++-6.dll"
  "libwinpthread-1.dll"
)

# Muhtemel arama dizinleri (kendi yolunu da ekleyebilirsin)
search_dirs=(
  "./"
  "$HOME/SFML"
  "$HOME/Documents/Codes/SFML/build-mingw/sfml-install/bin"
  "$HOME/Documents/Codes/SFML/bin"
  "$HOME/Downloads"
  "/usr/x86_64-w64-mingw32/bin"
  "/usr/i686-w64-mingw32/bin"
  "/usr/local/bin"
  "/usr/bin"
)

echo "DLL araması başlıyor..."
found_any=0
missing=()

for dll in "${dlls[@]}"; do
  # Zaten varsa atla
  if [ -f "./$dll" ]; then
    echo "Zaten mevcut: $dll"
    found_any=1
    continue
  fi

  found=""
  # Önce hızlıca arama dizinlerinde bak
  for d in "${search_dirs[@]}"; do
    if [ -d "$d" ]; then
      f=$(find "$d" -maxdepth 3 -type f -iname "$dll" 2>/dev/null | head -n 1 || true)
      if [ -n "$f" ]; then
        found="$f"
        break
      fi
    fi
  done

  # Bulunamadıysa ev dizininde daha geniş arama yap
  if [ -z "$found" ]; then
    f=$(find "$HOME" -type f -iname "$dll" 2>/dev/null | head -n 1 || true)
    if [ -n "$f" ]; then
      found="$f"
    fi
  fi

  if [ -n "$found" ]; then
    echo "Bulundu: $dll  -->  $found"
    cp -v "$found" ./
    found_any=1
  else
    echo "Bulunamadı: $dll"
    missing+=("$dll")
  fi
done

echo
if [ "${#missing[@]}" -eq 0 ]; then
  echo "Tüm DLL'ler bulundu/kopyalandı."
else
  echo "Aşağıdaki DLL'ler bulunamadı:"
  for m in "${missing[@]}"; do echo "  - $m"; done
  echo
  echo "Eğer bulunamayanlar varsa, SFML'in indirdiğin paketinin 'bin' klasörünü veya mingw bin klasörünü manuel kontrol et."
fi

# Opsiyonel: wine ile çalıştırmak ister misin?
read -p "Wine ile şimdi çalıştırmak ister misin? (y/N): " yn
case "$yn" in
  [Yy]* )
    if command -v wine >/dev/null 2>&1; then
      echo "Wine çalıştırılıyor..."
      wine pixelDriftWin.exe
    else
      echo "Wine yüklü görünmüyor. 'sudo apt install wine' ile kurabilirsin."
    fi
    ;;
  * )
    echo "Tamam. Kopyalama tamamlandı. 'wine pixelDriftWin.exe' ile çalıştırabilirsin."
    ;;
esac
