with import <nixpkgs> {};

# For Nix Users

stdenv.mkDerivation {
  name="Developpement environmnent";
  buildInputs = with pkgs; [
    SDL2.dev
    SDL2_ttf
    SDL2_mixer
    SDL2_image
  ];

  #NIX_CFLAGS_COMPILE = "-I ${pkgs.SDL2.dev}/include/SDL2";
}
