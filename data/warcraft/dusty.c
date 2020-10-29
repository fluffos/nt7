// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m趴趴熊[1;33m[2;37;0m[2;37;0m", ({"dustpp"}));        
        set("gender", "女性");                
        set("long", "这是一直奇异的玩偶小熊，它所到之处寸草不生。[2;37;0m
它是客官别怕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dusty");
        set("owner_name", "客官别怕");
        set_temp("owner", "dusty");
        set_temp("owner_name", "客官别怕");
        ::setup();
}
