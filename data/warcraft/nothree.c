// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"wtiger"}));        
        set("gender", "男性");                
        set("long", "一只大大大大的白虎。[2;37;0m
它是扈三娘的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nothree");
        set("owner_name", "扈三娘");
        set_temp("owner", "nothree");
        set_temp("owner_name", "扈三娘");
        ::setup();
}
