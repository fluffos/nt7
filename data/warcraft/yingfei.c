// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m浴火[2;37;0m[2;37;0m", ({"yuhuo"}));        
        set("gender", "女性");                
        set("long", "$N的$n[2;37;0m
它是黄颍妃的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yingfei");
        set("owner_name", "黄颍妃");
        set_temp("owner", "yingfei");
        set_temp("owner_name", "黄颍妃");
        ::setup();
}
