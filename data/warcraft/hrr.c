// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m拉[33m土[33m车[2;37;0m[2;37;0m", ({"hrrs"}));        
        set("gender", "男性");                
        set("long", "花绒绒的专用车[2;37;0m
它是花绒绒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hrr");
        set("owner_name", "花绒绒");
        set_temp("owner", "hrr");
        set_temp("owner_name", "花绒绒");
        ::setup();
}
