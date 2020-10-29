// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是钛炫的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xytaixuan");
        set("owner_name", "钛炫");
        set_temp("owner", "xytaixuan");
        set_temp("owner_name", "钛炫");
        ::setup();
}
