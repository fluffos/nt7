// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m利维坦贝希摩[2;37;0m[2;37;0m", ({"leviathan"}));        
        set("gender", "男性");                
        set("long", "哈利路亚！！！！！！！！！！！[2;37;0m
它是镶镶镶镶的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "sipilu");
        set("owner_name", "镶镶镶镶");
        set_temp("owner", "sipilu");
        set_temp("owner_name", "镶镶镶镶");
        ::setup();
}
