// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "神兽啊[2;37;0m
它是阿涛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "djt");
        set("owner_name", "阿涛");
        set_temp("owner", "djt");
        set_temp("owner_name", "阿涛");
        ::setup();
}
