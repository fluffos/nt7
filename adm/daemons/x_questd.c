// This program is a part of NITAN MudLIB
// /adm/daemons/x_questd.c 宗师口讯任务守护进程

#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

public int query_quest(object me, object ob)
{
    mapping temp, quest = ([]);
    string arg, msg, str/*, place, where*/, question, answer;
    object npc;
    object maze_target;
    object maze_object;

    temp = X_PointD->get_question();    //由守护程序产生点阵任务
    // temp =  ANTI_ROBOT->get_question();
    question = temp["question"];
    answer = temp["answer"];

    message("vision", sprintf("%s小声的对%s吩咐着什么，%s一边听，"
                              "一边不住的点头。\n",
                                ob->name(1), me->name(), me->name()),
                                environment(me), ({ me }));

    npc = new(CLASS_D("generate") + "/player_npc.c");   //生成收讯人
    FUBEN_D->clear_fuben("ultra",query("id", me));
    maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
    maze_object->set_maze_boss(npc);
    //maze_target = MAZE_D->create_maze(npc);
    maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
    npc->move(maze_target);
    npc->set_from_me(ob, 1);
    set_temp("quester",query("id",  me), npc);
    set("ultra_whisper",query("id",  me), npc);

    msg = sprintf("\n%s对你说道：你赶紧走一趟，将这个口讯传送"
                  "(whisper)给%s，据说他正在一个迷宫中，不得延误：\n",
                    ob->name(1), npc->name(1));
    msg += question;

    //quest["maze"]=query("maze/mazename", maze_target);
    quest["maze"] = maze_object;
    quest["object"] = base_name(npc);
    quest["bonus"] = 200+random(51);
    quest["name"] = npc->name(1);
    quest["id"]=query("id", npc);
    quest["answer"] = answer;
    quest["type"] = "传";
    switch(query("id", ob) )
    {
        case "dugu qiubai":
        quest["dgmsg"] = msg;
        str = "quest_dg";

        break;

        case "kuihua taijian":
        quest["khmsg"] = msg;
        arg = "player_npc";
        str = "quest_kh";
        break;

        case "huang shang":
        quest["msg"] = msg;
        str = "quest_hs";
        break;

        case "nanhai shenni":
        quest["msg"] = msg;
        str = "quest_sn";
        break;
    }

    set(str, quest, me);
    me->start_more(msg);

    return 1;
}