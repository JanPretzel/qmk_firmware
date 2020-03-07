# How to build and flash

```bash
$ make git-submodule
$ docker run --rm --workdir /qmk_firmware --privileged -v $(pwd):/qmk_firmware -v /dev:/dev qmkfm/base_container make ergodox_ez:jan_pretzel
$ wally-cli .build/ergodox_ez_jan_pretzel.hex
```
