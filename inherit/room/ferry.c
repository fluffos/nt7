
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();

void setup()
{
        object room;

        ::setup();

        if (room = find_object(query("boat")))
                delete("yell_trigger", room);
}

void init()
{
        add_action("do_yell", "yell");
}

int do_yell(string arg)
{
        string dir;

        if (! arg || arg == "") return 0;

        if (arg == "boat") arg = "船家";

        if( query("age", this_player())<14 )
                message_vision("$N使出吃奶的力气喊了一声：“" + 
                               arg + "”\n", this_player());
        else if( query("neili", this_player())>200 )
                message_vision("$N吸了口气，一声“" + arg + 
                               "”，声音中正平和地远远传"
                               "了出去。\n", this_player());
        else    message_vision("$N鼓足中气，长啸一声：“" + arg + 
                               "！”\n", this_player());

        if (arg == "船家") 
        {
                check_trigger();
                return 1;
        }else message_vision(query("name", this_object())+"面上远远传来一阵回声：“"+arg+
                               "～～～”\n", this_player());

        return 1;
}

void check_trigger()
{
        object room;
        string myboat;

        if( query("exits/enter", this_object()) )
        {
                message("vision", "岸边一只渡船上的老艄公说道：正等着你呢，上来吧。\n",
                        this_object());
                return;
        }

        if( !(room=find_object(myboat=query("boat", this_object()))) )
                room = load_object(myboat);

        if (! (room = find_object(myboat))) 
        {
                message("vision", "ERROR: boat not found\n", this_object());
                return;
        }

        if( query("yell_trigger", room) )
        {
                message("vision","只听得"+query("name", this_object())+"面上隐隐传来：“别急嘛，"
                        "这儿正忙着呐……”\n", this_object() );
                return;
        }

        set("yell_trigger", 1, room);
        set("exits/enter", myboat, this_object());
        set("exits/out", base_name(this_object()), room);

        message("vision", "一叶扁舟缓缓地驶了过来，艄公将一块踏脚"
                "板搭上堤岸，以便乘客\n上下。\n", this_object());
        message("vision", "艄公将一块踏脚板搭上堤岸，形成一个向上"
                "的阶梯。\n", room);

        remove_call_out("on_board");
        call_out("on_board", 15);
}

void on_board()
{
        object room;

        if( !query("exits/enter", this_object()) )
                return;

        message("vision","艄公把踏脚板收了起来，竹篙一点，扁舟向"+query("name", this_object())+"心驶去。\n",
                this_object());

        if (room = find_object(query("boat"))) 
        {
                delete("exits/out", room);
                message("vision", "艄公把踏脚板收起来，说了一声“坐稳喽”，"
                        "竹篙一点，扁舟向\n"+query("name", this_object())+"心驶去。\n",
                        room);
        }

        delete("exits/enter", this_object());

        remove_call_out("arrive");
        call_out("arrive", 20);
}

void arrive()
{
        object room;
        string myboat = query("boat");
        string myopp = query("opposite");

        if (room = find_object(myboat)) 
        {
                set("exits/out", myopp, room);
                message("vision", "艄公说“到啦，上岸吧”，随即把一块踏脚板"
                        "搭上堤岸。\n", 
                        room );
        }

        /*
        if( !(room = find_object(myopp)) )
                room = load_object(myopp);

        if( room = find_object(myopp) ) {
                set("exits/enter", myboat, room);
                message("vision", "一叶扁舟缓缓地驶了过来，艄公将一块踏脚"
                        "板搭上堤岸，以便乘客\n上下。\n", 
                        room);
        }
        */       

        remove_call_out("close_passage");
        call_out("close_passage", 20);
}

void close_passage()
{
        object room;

        if (room = find_object(query("boat"))) 
        {
                delete("exits/out", room);
                message("vision","艄公把踏脚板收起来，把扁舟驶向"+query("name", this_object())+"心。\n",
                room);
                delete("yell_trigger", room);
        }

        /*
        if( room=query("opposite", find_object(this_object()))){
                delete("exits/enter", room);
                message("vision","艄公把踏脚板收了起来，竹篙一点，扁舟向"+query("name", this_object())+"心驶去。\n",
                        room);
        }
        */
}
