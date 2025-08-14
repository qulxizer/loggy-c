# Maintainer: Mahdi Husain <qulxizer@gmail.com>
pkgname=loggy-c-git
pkgver=r0.0.1+$(date +%Y%m%d)
pkgrel=1
pkgdesc="Loggy – A lightweight C logger (built from git)"
arch=('x86_64')
url="https://github.com/qulxizer/loggy-c"
license=('MIT')
depends=()
makedepends=('cmake' 'gcc' 'git')
source=("git+$url")
sha256sums=('SKIP')

build() {
    cd "$srcdir/loggy-c"
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    cmake --build build
}

check() {
    cd "$srcdir/loggy-c/build"
    ctest --output-on-failure
}

package() {
    cd "$srcdir/loggy-c"
    cmake --install build --prefix="$pkgdir/usr"
}
