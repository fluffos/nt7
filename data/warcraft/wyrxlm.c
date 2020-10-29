// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m如意虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "魔幻如意老虎[2;37;0m
它是楚啸风的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wyrxlm");
        set("owner_name", "楚啸风");
        set_temp("owner", "wyrxlm");
        set_temp("owner_name", "楚啸风");
        ::setup();
}
