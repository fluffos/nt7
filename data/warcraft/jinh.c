// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m只为丸子而活[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "yuqing wan[2;37;0m
它是搓搓丸子的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jinh");
        set("owner_name", "搓搓丸子");
        set_temp("owner", "jinh");
        set_temp("owner_name", "搓搓丸子");
        ::setup();
}
