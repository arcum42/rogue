const std = @import("std");
const Build = std.build;

pub fn build(b: *Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "rogue",
        .optimize = optimize,
        .target = target,
    });
    exe.addCSourceFiles(&.{ "src/armor.c", "src/daemon.c", "src/fight.c", "src/monsters.c", "src/pack.c", "src/rip.c", "src/rooms.c", "src/state.c", "src/weapons.c", "src/chase.c", "src/daemons.c", "src/init.c", "src/list.c", "src/move.c", "src/passages.c", "src/save.c", "src/sticks.c", "src/wizard.c", "src/command.c", "src/extern.c", "src/mach_dep.c", "src/mdport.c", "src/new_level.c", "src/potions.c", "src/things.c", "src/xcrypt.c", "src/io.c", "src/main.c", "src/misc.c", "src/options.c", "src/rings.c", "src/scrolls.c", "src/vers.c" }, &.{
        "-std=c17",
        "-Wpedantic",
        "-Wall",
        "-Wextra",
        "-Wshadow",
    });

    exe.linkSystemLibrary("ncurses");
    exe.linkSystemLibrary("c");

    b.installArtifact(exe);

    const run = b.addRunArtifact(exe);
    run.step.dependOn(b.getInstallStep());
}
