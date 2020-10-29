// YangXiao.h

#include <ansi.h>

string* names = ({
        "zhuang zheng",
        "wen cangsong",
        "tang yang",
        "xin ran",
        "yan yuan",
        "xie xun",
        "wei yixiao",
});

string ask_me()
{
        mapping fam, my_fam, skl;
        object fighter, me, room, monk;
        string *sname;
        int i,j;

        fighter = this_player();
        me = this_object();
        my_fam=query("family", me);

        skl = fighter->query_skills();
        if (sizeof(skl) <= 1)
                return RANK_D->query_respect(fighter) +
                "功力不够，不够资格闯光明圣火阵。";
        sname  = keys(skl);
        for(i=0; i<sizeof(skl); i++) {
                if (skl[sname[i]] < 80)
                return RANK_D->query_respect(fighter) +
                "功力不够，不够资格闯光明圣火阵。";
        }

        if( query("guangming_winner", fighter) )
                return RANK_D->query_respect(fighter) +
                "已然闯过光明圣火阵，可不要拿杨逍开这等玩笑。";

        if( query("guilty", fighter)>0 )
                return RANK_D->query_respect(fighter) +
                "你累犯数戒，身带重罪，我如何能准许你闯光明圣火阵！";

        if( query("assigned_fighter", me) )
                return RANK_D->query_respect(fighter) +
                "，今日已有人挑战光明圣火阵，你过一段时间再来吧。";

        set_temp("yangxiao-asked", 1, fighter);

        say("\n杨逍说道：好吧，我召集谢韦二法王和五旗使在东侧殿集合，你稍候到前
边找我。\n");

        set("assigned_fighter",query("id",  fighter), me);

        if( !query_temp("fanyao-asked", fighter) )
        say("\n杨逍又道：请你速去告知范右使，请他即刻招集教主殷法王和五散人于西
侧殿集合。\n");

        message_vision("\n杨逍往南离开。\n\n", fighter);

// 1.
        if(!( room = find_object("/d/mingjiao/rjqdating")) )
        room = load_object("/d/mingjiao/rjqdating");
        me->move(room);
        if( !objectp(monk = present(names[0], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，五旗使中有人不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);
// 2.
        if(!( room = find_object("/d/mingjiao/jmqdating")) )
        room = load_object("/d/mingjiao/jmqdating");
        me->move(room);
        if( !objectp(monk = present(names[1], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，五旗使中有人不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);
// 3.
        if(!( room = find_object("/d/mingjiao/hsqdating")) )
        room = load_object("/d/mingjiao/hsqdating");
        me->move(room);
        if( !objectp(monk = present(names[2], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，五旗使中有人不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);
// 4.
        if(!( room = find_object("/d/mingjiao/lhqdating")) )
        room = load_object("/d/mingjiao/lhqdating");
        me->move(room);
        if( !objectp(monk = present(names[3], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，五旗使中有人不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);
// 5.
        if(!( room = find_object("/d/mingjiao/htqdating")) )
        room = load_object("/d/mingjiao/htqdating");
        me->move(room);
        if( !objectp(monk = present(names[4], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，五旗使中有人不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);
// 6.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[5], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，谢法王不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);
// 7.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[6], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n杨逍走了过来。\n\n", fighter);
                return "真是对不起，韦法王不在，无法举行光明圣火阵。\n";
        }
        message("vision","\n杨逍走了过来，跟"+query("name", monk)+"俯耳轻声说了几句。\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"点了点头，快步走了出去。\n",room,monk);

        me->move("/d/mingjiao/qiandian");
        call_out("waiting", 1, me);
        return "好！大家都出来了。\n";
}

int waiting(object me)
{
        object fighter;
        int wait_time;

        if( wait_time == 300 )
        {
                say( "杨逍说道：看来他不会来了，我们回去罢！\n\n");
                call_out("do_back", 0, me);
        }

        if( !objectp(fighter=present(query("assigned_fighter", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me);
        }
        else if( !present("fanyao",environment(me)) || !query_temp("fanyao-asked", fighter) )
        {
                if( random(10) == 0 )
                say("\n杨逍说道：" + RANK_D->query_respect(fighter) + "去请了范右使没有？ 照理他现在该到了罢？\n");

                wait_time++;
                call_out("waiting", 1, me);
        }
        else         call_out("preparing", 1, me, fighter);

        return 1;
}

int preparing(object me, object fighter)
{
        object monk, room, ob;

        if(!( room = find_object("/d/mingjiao/qiandian")) )
        room = load_object("/d/mingjiao/qiandian");

        message("vision", HIY "\n杨逍大声宣布：东光明圣火阵合围！\n" NOR, room);
        message("vision", "\n只听四周响起沙沙的脚步声，三法王五散人五旗使们个个神情肃杀，\n"
                "或赤手空拳，或手持兵器，慢慢地围了上来，堵住了通路。\n\n", room);
        delete("exits", room);

        say( "杨逍又道：准备，光明圣火阵即刻发动！\n\n");

        delete_temp("yangxiao-asked", fighter);
        delete_temp("beat_count", fighter);
        set_temp("fighting", 1, fighter);

        call_out("fighting", 10, me, fighter, 0);
        return 1;
}

int fighting(object me, object fighter, int count)
{
        object monk1, monk2, room1, room2;

        if(!( room1 = find_object("/d/mingjiao/eastdian")) )
        room1 = load_object("/d/mingjiao/eastdian");

        if(!( room2 = find_object("/d/mingjiao/qiandian")) )
        room2 = load_object("/d/mingjiao/qiandian");

        if( count <= 6 )
        {
                message("vision", "\n光明圣火阵急速地旋转着，一层层地向内收紧！\n" NOR, room2);
                monk1 = present(names[count], room1);
                if (monk1) monk1->move(room2);
        }

        if( count >= 1 && count <= 7 ) {
                monk2 = present(names[count-1], room2);
                if (monk2) monk2->move(room1);
        }

        if( !find_player(query("assigned_fighter", me)) || 
        !living(fighter) || query("qi", fighter) <= 1 )
        {
                if( objectp(present(query("assigned_fighter", me),environment(me)))){
                        delete_temp("fighting", fighter);
                        delete_temp("beat_count", fighter);
                }
                monk1->move(room1);

                say( "杨逍摇了摇头，说道：想不到 ... 唉！\n\n");
                command("sigh");
                call_out("do_back", 5, me );
        }
        else if( count >= 7 )
        {
                if( query_temp("beat_count", fighter) >= 14 )
                        call_out("do_recruit", 5, me, fighter);
                else
                        call_out("do_back", 5, me );
        }
        else
        {
                count++;
                call_out("fighting", 2, me, fighter, count);
        }

        return 1;
}

int do_recruit(object me, object fighter)
{
        mapping ft_fam, my_fam;

        delete_temp("beat_count", fighter);
        delete_temp("fighting", fighter);
        addn("combat_exp", 10000, fighter);
        set("guangming_winner", 1, fighter);

        if( !(ft_fam=query("family", fighter)) || ft_fam["family_name"] != "明教" )
        {
                command("bow");
                say("杨逍说道：" + RANK_D->query_respect(fighter) + "此番过阵，当对本身修行大有助益，百尺竿头，更进一步，杨逍就此别过！\n");
                call_out("do_back", 5, me );
        }
        else
        {
                say("\n杨逍说道：恭喜你闯过了光明圣火阵！本教有此等杰出弟子，届时必当为武林放一异彩！\n");
                call_out("do_back", 5, me );
        }
        return 1;
}

int do_back(object me)
{
        object monk, room1, room2;
        int i;

        message("vision", "\n杨逍挥了挥手， 五旗使和二法王随即鱼贯离开前殿。\n", environment(me) );

        if(!( room1 = find_object("/d/mingjiao/eastdian")) )
        room1 = load_object("/d/mingjiao/eastdian");

        for(i = 1; i <= 7; i ++)
        {
                switch (i)
                {
                case 1:
                        if(!( room2 = find_object("/d/mingjiao/rjqdating")) )
                        room2 = load_object("/d/mingjiao/rjqdating");
                        break;
                case 2:
                        if(!( room2 = find_object("/d/mingjiao/jmqdating")) )
                        room2 = load_object("/d/mingjiao/jmqdating");
                        break;
                case 3:
                        if(!( room2 = find_object("/d/mingjiao/hsqdating")) )
                        room2 = load_object("/d/mingjiao/hsqdating");
                        break;
                case 4:
                        if(!( room2 = find_object("/d/mingjiao/lhqdating")) )
                        room2 = load_object("/d/mingjiao/lhqdating");
                        break;
                case 5:
                        if(!( room2 = find_object("/d/mingjiao/htqdating")) )
                        room2 = load_object("/d/mingjiao/htqdating");
                        break;
                case 6:
                case 7:
                        if(!( room2 = find_object("/d/mingjiao/dadian")) )
                        room2 = load_object("/d/mingjiao/dadian");
                        break;
                }
                if( objectp( monk = present(names[i-1], room1) ));
                monk->move(room2);
        }

        delete("assigned_fighter", me);
        me->move("/d/mingjiao/dadian");

        return 1;
}

#include "shizhe.h"
