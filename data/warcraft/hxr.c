// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大笨鸟[2;37;0m[2;37;0m", ({"hxrds"}));        
        set("gender", "女性");                
        set("long", "一只笨死的鸟，不过因为是朱雀，所以没死成。。。汗[2;37;0m
它是黄小蓉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hxr");
        set("owner_name", "黄小蓉");
        set_temp("owner", "hxr");
        set_temp("owner_name", "黄小蓉");
        ::setup();
}
