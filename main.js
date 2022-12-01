const r = require('raylib');
const fs = require('fs');

var mqq = require("./maquina");
var data;

function load()
{
	//FONTS
	data.file.font.push(r.LoadFontEx("data/font/acentos/KyrillaSansSerif-Bold.ttf", 16, 0, 0));
	data.file.font.push(r.LoadFontEx("data/font/Mockery.ttf", 48, 0, 0));
	data.file.font.push(r.LoadFontEx("data/font/Mockery.ttf", 24, 0, 0));
	//MUSIC
	data.file.music.push(r.LoadMusicStream("data/audio/music/maintheme_by_kayoa.mp3"));
	//MODELS
	data.file.loadModel("lvl0_map0","data/models/map/level0/0.glb",false);
	data.file.loadModel("lvl0_props0","data/models/map/level0/props/0.glb",true);
	data.file.loadModel("lvl0_hitbox0","data/models/map/level0/hitbox/hitbox0.glb",true);
	data.file.loadModel("lvl0_hitbox1","data/models/map/level0/hitbox/hitbox1.glb",true);
	data.file.loadModel("lvl0_hitbox2","data/models/map/level0/hitbox/hitbox2.glb",true);
	data.file.loadModel("lvl0_hitbox3","data/models/map/level0/hitbox/hitbox3.glb",true);
	data.file.loadModel("lvl0_hitbox4","data/models/map/level0/hitbox/hitbox4.glb",true);
	data.file.loadModel("lvl0_hitbox5","data/models/map/level0/hitbox/hitbox5.glb",true);
	data.file.loadModel("lvl0_hitbox6","data/models/map/level0/hitbox/hitbox6.glb",true);
	data.file.loadModel("lvl0_hitbox7","data/models/map/level0/hitbox/hitbox7.glb",true);
	data.file.loadModel("lvl0_hitbox8","data/models/map/level0/hitbox/hitbox8.glb",true);
	data.file.loadModel("lvl0_hitbox9","data/models/map/level0/hitbox/hitbox9.glb",true);
	data.file.loadModel("lvl0_hitbox10","data/models/map/level0/hitbox/chao.glb",true);
	data.file.loadModel("lvl0_map0item0","data/models/map/level0/item/0.glb",true);
	data.file.loadModel("lvl0_map0item1","data/models/map/level0/item/1.glb",true);
	data.file.loadModel("lvl0_map0item2","data/models/map/level0/item/2.glb",true);
	data.file.loadModel("lvl0_map0item3","data/models/map/level0/item/3.glb",true);
	data.file.loadModel("lvl0_area0","data/models/map/level0/area/0.glb",true);
	data.file.loadModel("lvl0_area1","data/models/map/level0/area/1.glb",true);
	data.file.loadModel("lvl0_area2","data/models/map/level0/area/2.glb",true);
	data.file.loadModel("lvl0_area3","data/models/map/level0/area/3.glb",true);
	data.file.loadModel("lvl0_area4","data/models/map/level0/area/4.glb",true);
	data.file.loadModel("lvl0_area5","data/models/map/level0/area/5.glb",true);
	data.file.loadModel("player-idle","data/models/player/idle/",false);
	data.file.loadModel("player-walk","data/models/player/walk/",false);
}

const Teclado =
{
	gameplay: 
	{
		escMenu: 
		[
			{//exit the current menu(possibly go back to another menu, or go back to the game)
				text:"return",
				func:function(){Teclado.gameplay.escMenu.offload = true;}
			},
			{//exit(to OS)
				text:"exit",
				func:function(){Teclado.gameplay.escMenu.data.session.exit = true;Teclado.gameplay.escMenu.offload = true;}, 
			},
		],
		pressed:
		{
			w:function(data)
			{
				data.scene.render.model['joao451'].progression = 1;
				data.scene.render.model['joao451'].id = 'player-walk';
			},
			s:function(data)
			{
				data.scene.render.model['joao451'].progression = -1;
				data.scene.render.model['joao451'].id = 'player-walk';
			},
		},
		down:
		{
			w:function(data)
			{
				if(mqq.PlayerCollider(data,data.scene.render.model['joao451'],false)==false)
				{
					mqq.Move3D(data.scene.creature['joao451'].position,data.scene.creature['joao451'].rotation.y,0.1);
				}
			},
			s:function(data)
			{
				if(mqq.PlayerCollider(data,data.scene.render.model['joao451'],true)==false)
				{
					mqq.Move3D(data.scene.creature['joao451'].position,data.scene.creature['joao451'].rotation.y,-0.1);
				}
			},
			a:function(data)
			{
				data.scene.creature['joao451'].rotation.y += 6;
				data.scene.creature['joao451'].rotation.y = mqq.limito(data.scene.creature['joao451'].rotation.y,0,359);
			},
			d:function(data)
			{
				data.scene.creature['joao451'].rotation.y -= 6;
				data.scene.creature['joao451'].rotation.y = mqq.limito(data.scene.creature['joao451'].rotation.y,0,359);
			},
			space:function(data)
			{
				data.scene.creature['joao451'].position.y += 0.1;
			},
		},
		released:
		{
			w:function(data)
			{
				data.scene.render.model['joao451'].progression = 1;
				data.scene.render.model['joao451'].id = 'player-idle';
			},
			s:function(data)
			{
				data.scene.render.model['joao451'].progression = 1;
				data.scene.render.model['joao451'].id = 'player-idle';
			},
		},
		useThis:function(data)
		{
			data.keyboard.set(r.KEY_ESCAPE,'pressed',mqq.Menu,[Teclado.gameplay.escMenu,data]);
			data.keyboard.set(r.KEY_W,'down',this.down.w,[data]);
			data.keyboard.set(r.KEY_W,'pressed',this.pressed.w,[data]);
			data.keyboard.set(r.KEY_W,'released',this.released.w,[data]);
			data.keyboard.set(r.KEY_S,'down',this.down.s,[data]);
			data.keyboard.set(r.KEY_S,'pressed',this.pressed.s,[data]);
			data.keyboard.set(r.KEY_S,'released',this.released.s,[data]);
			data.keyboard.set(r.KEY_A,'down',this.down.a,[data]);
			data.keyboard.set(r.KEY_D,'down',this.down.d,[data]);
			data.keyboard.set(r.KEY_SPACE,'down',this.down.space,[data]);
			data.keyboard.set(r.KEY_G,'pressed',mqq.Save,[data]);
		}
	}
}

function main()
{
	data = new mqq.Data();//all startup needs are in the constructor
	load();
	var startMenu = 
	[
		{//exit the current menu(possibly go back to another menu, or go back to the game)
			text:"jogar",
			func:function(){startMenu.offload = true;}
		},
		{//exit(to OS)
			text:"sair",
			func:function(){startMenu.data.session.exit = true;startMenu.offload = true;}, 
		},
	];
	startMenu.logo = true;
	mqq.Menu(startMenu,data);
	delete startMenu;
	
	data.scene.creature.push
	(
		{
			name:"joao451",
			type:"human",
			position:{x:0,y:4,z:0},
			rotation:{x:0,y:0,z:0},
			speed:0.1,
			alive:true,
			active:true
		}
	);
	
	data.scene.creature['joao451'] = data.scene.creature[0];
	data.scene.render.addCreature(data.scene.creature['joao451']);
	data.scene.render.addModel('map0','lvl0_map0');
	data.scene.render.addText('build',0,data.config.title + " versão " + (data.config.build/10000),r.Vector2(0,(data.config.screen.y)-16),mqq.COR_PRETO,true);
	r.UpdateCamera(data.scene.camera);
    data.scene.camera.target = data.scene.creature[0].position;
    data.scene.camera.position = {x:0.4375, y:10, z:11.0625};
	
	for(let i = 0;i<data.file.hitbox.length;i++)
		if(data.file.hitbox[i].name.includes('lvl0_hitbox'))
		{
			data.scene.render.addHitbox(data.file.hitbox[i].name,data.file.hitbox[i].hitbox);
		}
	Teclado.gameplay.useThis(data);
    while(!r.WindowShouldClose() && data.session.exit == false)
    {
        data.session.frame++;
		data.keyboard.run(data);
		if(data.session.frame%(Math.floor(data.config.framerate/60.0))==0)
		{
			mqq.Gravit(data,data.scene.render.model[0]);
		}
		mqq.Render(data);
    }
    //CloseAudioDevice();--------------------------------------------------------------------------------------
	r.CloseWindow();
	//app.quit();
}
main();
//app.on('ready', main);//change this from RaylibDemo to main when engine fully ported from c