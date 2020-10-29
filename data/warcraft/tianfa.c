// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m翼虎[2;37;0m[2;37;0m", ({"tianfaz"}));        
        set("gender", "男性");                
        set("long", "翼虎[2;37;0m
它是天罚的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tianfa");
        set("owner_name", "天罚");
        set_temp("owner", "tianfa");
        set_temp("owner_name", "天罚");
        ::setup();
}
