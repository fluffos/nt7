// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m百足之虫[2;37;0m[2;37;0m", ({"lauwdbb"}));        
        set("gender", "女性");                
        set("long", "我的百足虫，哇哈哈！[2;37;0m
它是不毒老人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lauwd");
        set("owner_name", "不毒老人");
        set_temp("owner", "lauwd");
        set_temp("owner_name", "不毒老人");
        ::setup();
}
