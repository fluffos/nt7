// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m风儿[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "这就是天下闻名的奇兽麒麟，驰骋天下的座驾![2;37;0m
它是朱玲玲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lingling");
        set("owner_name", "朱玲玲");
        set_temp("owner", "lingling");
        set_temp("owner_name", "朱玲玲");
        ::setup();
}
