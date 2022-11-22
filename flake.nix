{
  description = "Flake utils demo";

  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system}; in
      {
        packages = rec {
          game = pkgs.stdenv.mkDerivation {
            name = "game";
            installPhase = ''
              mkdir -p $out/bin
              cp game.out $out/bin/game 
            '';
            buildInputs = with pkgs; [
              pkg-config xorg.libX11 libGL
            ];
            src = ./.;
          };
          default = game;
        };
      }
    );
}
