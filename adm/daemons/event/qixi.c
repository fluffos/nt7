// qixi.c 事件：七夕牛郎织女星相会
// couple/id 如果结婚则奖励加倍
#include <ansi.h>

void create() { seteuid(getuid()); }

#define STATUS_PROMPT           1
#define STATUS_START            2
#define STATUS_END              3

// 开始创建事件
void create_event()
{
        // 明年7月7日牛郎织女星相会，提前一天提示
        EVENT_D->at_after(1, -7, -6, -12, STATUS_PROMPT);
}

// 奖励
private void do_bonus(object room)
{
        object *obs;
        string msg;
        int r;
        int p = 1;
        int i;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        msg = HIW "\n只见天际群星光芒齐放，鹊桥隐现，牛郎织女之星光华闪耀，\n"
                  "会聚于鹊桥之上，刹那间，群星围绕，流光溢彩，一番盛大\n"
                  "景象。正所谓：\n" HIY
                  "　　    维天有汉，监亦有光。\n"
                  "        岐彼织女，终日七襄。\n"
                  "        虽则七襄，不成报章。\n"
                  "        睕彼牵牛，不以报箱。\n" HIW
                  "令人毕生难忘，又有古诗云：\n" HIY
                  "　　    迢迢牵牛星，皎皎河汉女。\n"
                  "        纤纤灌素手，札札弄机杼；\n"
                  "        终日不成章，泣涕零如雨。\n"
                  "        河汉清且浅，相去复几许?\n"
                  "        盈盈一水问，脉脉不得语。\n" NOR;

        message("vision", msg, obs);
        msg = "听说七月初七" + implode(sizeof(obs) > 4 ? obs[0..3]->name(1) : obs->name(1), "、") +
              "等人在望月台观赏牛郎织女星相会。";

        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        obs=filter_array(obs,(:query("combat_exp", $1) >= 10000:));
        if (sizeof(obs) < 1)
                return;

        msg = HIG "你望着浩瀚的天际以及牛郎星与织女星发出耀眼的光芒，似乎若有所思。\n" NOR;
        message("vision", msg, obs);

        for( i=0; i<sizeof(obs); i++ )
        {
                // 已经结婚的则奖励加倍
                if( stringp(query("couple/id", obs[i])))
                {
                        if (query("combat_exp", obs[i]) < 1000000000)
                                addn("combat_exp", 3000 * p*2, obs[i]);
                        obs[i]->improve_potential(1000 * p*2 + random(1000 * p*2));
                        obs[i]->improve_skill("martial-cognize", 1000 * p*2 + random(1000* p*2), 1);
                        addn("magic_points", 30*p*2+random(21*p*2), obs[i]);
                }
                else
                {
                        if (query("combat_exp", obs[i]) < 1000000000)
                                addn("combat_exp", 3000 * p, obs[i]);
                        obs[i]->improve_potential(1000 * p + random(1000 * p));
                        obs[i]->improve_skill("martial-cognize", 1000 * p + random(1000* p), 1);
                        addn("magic_points", 30*p+random(21*p), obs[i]);
                }
        }
        MAP_D->record_rumor(obs, "望月台七夕盛景", this_object());
}

// 事件触发
void trigger_event(int status)
{
        object room;

        room = find_object("/d/henshan/wangyuetai");

        // 钱塘江潮信
        switch (status)
        {
        case STATUS_PROMPT:
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "七月初七又要到了，听说不少人前往望月台观赏牛郎织女星相会。");
                // 明天18点钟相会
                EVENT_D->at_after(0, 0, 1, -18, STATUS_START);
                break;

        case STATUS_START:
                if (objectp(room))
                        do_bonus(room);
                // 一个小时以后完毕
                EVENT_D->at_after(0, 0, 0, 1, STATUS_END);
                break;

        case STATUS_END:
                if (objectp(room))
                        message("vision", "天际逐渐暗淡了下来，恢复了平静，你这才"
                                          "仿佛从梦中醒了过来。\n", room);
                // 继续执行default中的内容

        default:
                create_event();
                break;
        }
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "望月台七夕盛景":
                return "每年七月初七牛郎星与织女星在鹊桥相会，非常准时，故称之为七夕盛景色。每次两星相会"
                       "时群星闪耀，光彩照人，场面甚是壮观。\n";
        }
}

