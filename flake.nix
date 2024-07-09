{
  inputs = {
    nixpkgs.url = "github:StarGate01/nixpkgs/libnfc-nci";
  };

  outputs = { self, nixpkgs }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
    in
    {
      devShell.x86_64-linux =
        pkgs.mkShell {
          shellHook = ''
          '';

          buildInputs = with pkgs; [
            gdb
            gcc
            pkg-config
            cmake
            gnumake
            libnfc-nci
          ];
        };
    };
}
