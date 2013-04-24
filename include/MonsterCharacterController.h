#ifndef __Monster_H__
#define __Monster_H__

#include "Ogre.h"
#include "OIS.h"
#include "MovableText.h"
using namespace Ogre;

#define NUM_ANIMS 14//13           // number of animations the character has
#define CHAR_HEIGHT 5          // height of character's center of mass above ground
#define CAM_HEIGHT 2           // height of camera above character's center of mass
#define RUN_SPEED 17           // character running speed in units per second
#define TURN_SPEED 500.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second（加速度）
#define GRAVITY 90.0f          // gravity in downward units per squared second

class MonsterCharacterController
{
private:

	// all the animations our character has, and a null ID
	// some of these affect separate body parts and will be blended together
	//enum AnimID
	//{
	//	//ANIM_IDLE_BASE,
	//	//ANIM_IDLE_TOP,
	//	//ANIM_RUN_BASE,
	//	//ANIM_RUN_TOP,
	//	//ANIM_HANDS_CLOSED,
	//	//ANIM_HANDS_RELAXED,
	//	//ANIM_DRAW_SWORDS,
	//	//ANIM_SLICE_VERTICAL,
	//	//ANIM_SLICE_HORIZONTAL,
	//	//ANIM_DANCE,
	//	//ANIM_JUMP_START,
	//	//ANIM_JUMP_LOOP,
	//	//ANIM_JUMP_END,
	//	//ANIM_NONE
	//};

	enum AnimID
	{
		ANIM_Waiting_Stance_BASE,
		ANIM_Intro_Walk_BASE,
		ANIM_Attack_Special_02,
		ANIM_Attack_Special_03,
		ANIM_Attack_Special_04,
		ANIM_Attack_Special_05,
		ANIM_Attack_Special_06,
		//ANIM_Attack_Special_07,
		ANIM_Attack_Special_08,
		ANIM_Attack_Special_09,
		ANIM_Attack_Special_10,
		ANIM_Attack_Special_11,
		ANIM_Attack_Special_12,
		ANIM_Attack_Special_13,
		ANIM_Death_BASE,
		ANIM_NONE
	};

public:
	
	MonsterCharacterController(SceneManager* cam)
	{
		setupBody(cam);//->getSceneManager());
		mBodyNode->setScale(0.2,0.2,0.2);
		//setupCamera(cam);

		setupAnimations();
	}

	void addTime(Real deltaTime)
	{
		updateBody(deltaTime);
		updateAnimations(deltaTime);

		//updateCamera(deltaTime);
	}


	bool AI(int act)
	{
		Real x1,y1,z1,x2,y2,z2;
		x2=this->mBodyNode->getPosition().x;
		y2=this->mBodyNode->getPosition().y;
		z2=this->mBodyNode->getPosition().z;
		x1=this->mFighter->getPosition().x;
		y1=this->mFighter->getPosition().y;
		z1=this->mFighter->getPosition().z;
		this->mdistance=this->mBodyNode->getPosition().distance(this->mFighter->getPosition());//17->很靠近
		if(mdistance <=40)
		{
			//switch(act)
			
			//{
			if(act > 6 && act < 13)
			{
					//this->mAnims[this->ANIM_Waiting_Stance_BASE]->setLoop(true);
					/*mKeyDirection.z = z1 - z2;
					mKeyDirection.x = x1 - x2;*/
					this->mBodyNode->setDirection(mBodyNode->getPosition()-this->mFighter->getPosition(),Ogre::Node::TS_WORLD);
					this->mBodyNode->yaw(Ogre::Degree(180));
					if(this->mBaseAnimID == 0 || this->mBaseAnimID == 1 || this->mAnims[mBaseAnimID]->hasEnded())
					{
						srand(time(0));
						int react = rand() % 11 + 2;
						this->setBaseAnimation(AnimID(react),true);//this->ANIM_Attack_Special_02
					}
			}
			else
			{
				//this->setBaseAnimation(this->ANIM_Intro_Walk_BASE,false);
					this->mBodyNode->setDirection(mBodyNode->getPosition()-this->mFighter->getPosition(),Ogre::Node::TS_WORLD);
					this->mBodyNode->yaw(Ogre::Degree(180));

					if(this->mBaseAnimID == 0 || this->mBaseAnimID == 1 || this->mAnims[mBaseAnimID]->hasEnded())
					{	
						if(mdistance < 31)
							this->setBaseAnimation(this->ANIM_Attack_Special_03,true);
						else
							this->setBaseAnimation(this->ANIM_Intro_Walk_BASE,true);
					}

					/*mKeyDirection.z = z1 - z2;
					mKeyDirection.x = x1 - x2;*/
			}
		}

		//mBodyNode->translate(Vector3(x2,y2,z2));
		
		//this->mBodyNode->setDirection(mBodyNode->getPosition()-this->mFighter->getPosition(),Ogre::Node::TS_WORLD);
		//int d,f;
		//d =this->mdistance;
		//int b2=this->mAnimslevel[this->mBaseAnimID];
		//int b1=(AnimID)act;
		//if(d<10)
		//{

		//}
	
		return true;
	}

	bool Action(AnimID act)
	{
		if(this->mBaseAnimID>this->ANIM_Intro_Walk_BASE||this->mAnims[this->mBaseAnimID]->hasEnded())
		{

		}else
		return false;

			return true;
	}


private:

	void setupBody(SceneManager* sceneMgr)
	{
		// create main model
		mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3::UNIT_Y * CHAR_HEIGHT);
		
		mBodyEnt = sceneMgr->createEntity("MonsterBody", "Waiting_Stance.mesh");
		////mBodyEnt = sceneMgr->createEntity("SinbadBody", "runs.mesh");
		mBodyEnt->setCastShadows(true);
		mBodyNode->attachObject(mBodyEnt);
		this->mFighter=(Ogre::SceneNode*)sceneMgr->getRootSceneNode()->getChild("Player");
	//	mBodyNode->setFixedYawAxis(true,Vector3::UNIT_X);
		//mBodyNode->setAutoTracking(true,(Ogre::SceneNode*)sceneMgr->getRootSceneNode()->getChild("Player")->getChild("CamNode"),Vector3::NEGATIVE_UNIT_Y);
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Intro_Walk.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_02.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Big_Center.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_04.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_05.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_06.skeleton");
		//mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_07.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_08.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_09.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_10.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_11.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_12.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Attack_Special_13.skeleton");
		mBodyEnt->getSkeleton()->addLinkedSkeletonAnimationSource("Death.skeleton");



		mBodyEnt->refreshAvailableAnimationState();

		//// create swords and attach to sheath
		//LogManager::getSingleton().logMessage("Creating swords");
		//mSword1 = sceneMgr->createEntity("SinbadSword1", "Sword.mesh");
		//mSword2 = sceneMgr->createEntity("SinbadSword2", "Sword.mesh");
		//mBodyEnt->attachObjectToBone("Sheath.L", mSword1);
		//mBodyEnt->attachObjectToBone("Sheath.R", mSword2);

		LogManager::getSingleton().logMessage("Creating the chains");
		//// create a couple of ribbon trails for the swords, just for fun
		NameValuePairList params;
		params["numberOfChains"] = "2";
		params["maxElements"] = "80";
		//mSwordTrail = (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
		//mSwordTrail->setMaterialName("Examples/LightRibbonTrail");
		//mSwordTrail->setTrailLength(20);
		//mSwordTrail->setVisible(false);
		//sceneMgr->getRootSceneNode()->attachObject(mSwordTrail);


		//for (int i = 0; i < 2; i++)
		//{
		//	mSwordTrail->setInitialColour(i, 1, 0.8, 0);
		//	mSwordTrail->setColourChange(i, 0.75, 1.25, 1.25, 1.25);
		//	mSwordTrail->setWidthChange(i, 1);
		//	mSwordTrail->setInitialWidth(i, 0.5);
		//}

		mKeyDirection = Vector3::ZERO;
		mVerticalVelocity = 0;
		m_raySceneQuery=sceneMgr->createRayQuery( Ogre::Ray(this->mBodyNode->getPosition(),Ogre::Vector3::UNIT_Y));
		clampToTerrain();

		
		monsterInfo = new Ogre::MovableText("monsterInfo", "Monster\n2000/2000");
		monsterInfo->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
		monsterInfo->setCharacterHeight( 9.0f );
		monsterInfo->setColor(Ogre::ColourValue(1.0,0,0));
		monsterInfo->setGlobalTranslation(Ogre::Vector3(0,30,0));
		mBodyNode->attachObject(monsterInfo);
		getHurt = new Ogre::MovableText("getHurt", "HP");
		getHurt->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
		getHurt->setCharacterHeight( 20.0f );
		getHurt->setColor(Ogre::ColourValue(0,0,1.0));
		getHurt->setGlobalTranslation(Ogre::Vector3(0,35,0));
		mBodyNode->attachObject(getHurt);
		HP = 2000;
	}

	void setupAnimations()
	{
		// this is very important due to the nature of the exported animations
		mBodyEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

		//String animNames[] =
		//{"IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
		//"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd"};

		String animNames[] = 
		{"Waiting_Stance","Intro_Walk","Attack_Special_02","Attack_Big_Center","Attack_Special_04","Attack_Special_05","Attack_Special_06"
		,"Attack_Special_08","Attack_Special_09","Attack_Special_10","Attack_Special_11","Attack_Special_12"
		,"Attack_Special_13","Death"};
		Real level[]={0,0,1,1,1,1,1,1,1,1,1,1,2};
		// populate our animation list
		mAnims[this->ANIM_Waiting_Stance_BASE] = mBodyEnt->getAnimationState(animNames[this->ANIM_Waiting_Stance_BASE]);
		this->mAnims[this->ANIM_Waiting_Stance_BASE]->setLoop(true);
		this->mAnims[this->ANIM_Waiting_Stance_BASE]->setEnabled(false);
		this->mAnimslevel[this->ANIM_Waiting_Stance_BASE]=level[this->ANIM_Waiting_Stance_BASE];
		mAnims[this->ANIM_Intro_Walk_BASE] = mBodyEnt->getAnimationState(animNames[this->ANIM_Intro_Walk_BASE]);
		this->mAnims[this->ANIM_Intro_Walk_BASE]->setLoop(true);
		this->mAnims[this->ANIM_Intro_Walk_BASE]->setEnabled(false);
		this->mAnimslevel[this->ANIM_Intro_Walk_BASE]=level[this->ANIM_Intro_Walk_BASE];
		for (int i = 2; i < NUM_ANIMS; i++)
		{
			mAnims[i] = mBodyEnt->getAnimationState(animNames[i]);
			mAnims[i]->setLoop(false);
			this->mAnimslevel[i]=level[i];
			mFadingIn[i] = false;
			mFadingOut[i] = false;
		}

		//// start off in the idle state (top and bottom together)
		setBaseAnimation(ANIM_Waiting_Stance_BASE);
		//setTopAnimation(ANIM_IDLE_TOP);

		//// relax the hands since we're not holding anything
		//mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);

		//mSwordsDrawn = false;
	}

	void setupCamera(Camera* cam)
	{
		// create a pivot at roughly the character's shoulder
		//pivot放置在角色的肩膀处，在帧循环里同步这个位置永远不变
		mCameraPivot = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		// this is where the camera should be soon, and it spins around the pivot
		//goal作为pivot的子节点，放置在(0 ,0 , 15)处，也就是说goal永远会在pivot的正后方
		mCameraGoal = mCameraPivot->createChildSceneNode(Vector3(0, 0, 15));
		// this is where the camera actually is
		mCameraNode = cam->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mCameraNode->setPosition(mCameraPivot->getPosition() + mCameraGoal->getPosition());
		

		mCameraPivot->setFixedYawAxis(true);
		mCameraGoal->setFixedYawAxis(true);
		mCameraNode->setFixedYawAxis(true);

		// our model is quite small, so reduce the clipping planes
		cam->setNearClipDistance(0.1);
		cam->setFarClipDistance(10000);
		mCameraNode->attachObject(cam);


		//mPivotPitch = 0;
	}
public:
	void updateBody(Real deltaTime)
	{
		this->mBodyNode->setDirection(this->mFighter->getPosition()-this->mBodyNode->getPosition(),Ogre::Node::TS_WORLD);
		this->mBodyNode->yaw(Ogre::Degree(180));

		mGoalDirection = Vector3::ZERO;   // we will calculate this
		this->clampToTerrain();
		if (1||mKeyDirection != Vector3::ZERO)// && mBaseAnimID != ANIM_DANCE)
		{
			// calculate actually goal direction in world based on player's key directions
			//mGoalDirection += mKeyDirection.z * mCameraNode->getOrientation().zAxis();
			//mGoalDirection += mKeyDirection.x * mCameraNode->getOrientation().xAxis();
			mGoalDirection += mKeyDirection.z * mBodyNode->getOrientation().zAxis();
			mGoalDirection += mKeyDirection.x * mBodyNode->getOrientation().xAxis();
			mGoalDirection.y = 0;
			mGoalDirection.normalise();

			Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo(mGoalDirection);

			// calculate how much the character has to turn to face goal direction
			Real yawToGoal = toGoal.getYaw().valueDegrees();
			// this is how much the character CAN turn this frame
			Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
			// reduce "turnability" if we're in midair/****....Omitted.....****/
			//if (mBaseAnimID == ANIM_JUMP_LOOP) yawAtSpeed *= 0.2f;

			// turn as much as we can, but not more than we need to
			if (yawToGoal < 0) yawToGoal = std::min<Real>(0, std::max<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
			else if (yawToGoal > 0) yawToGoal = std::max<Real>(0, std::min<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);
			
			//mBodyNode->yaw(Degree(yawToGoal));

			// move in current body direction (not the goal direction)
			if(mdistance > 30)
			mBodyNode->translate(0, 0, deltaTime * RUN_SPEED,// * mAnims[mBaseAnimID]->getWeight(),
				Node::TS_LOCAL);
		}

		//if (mBaseAnimID == ANIM_JUMP_LOOP)
		//{
		//	// if we're jumping, add a vertical offset too, and apply gravity
		//	mBodyNode->translate(0, mVerticalVelocity * deltaTime, 0, Node::TS_LOCAL);
		//	mVerticalVelocity -= GRAVITY * deltaTime;
		//	
		//	Vector3 pos = mBodyNode->getPosition();
		//	if (pos.y <= CHAR_HEIGHT)
		//	{
		//		// if we've hit the ground, change to landing state
		//		pos.y = CHAR_HEIGHT;
		//		mBodyNode->setPosition(pos);
		//		setBaseAnimation(ANIM_JUMP_END, true);
		//		mTimer = 0;
		//	}
		//}
	}

	void updateAnimations(Real deltaTime)
	{
		Real baseAnimSpeed = 1;
		//Real topAnimSpeed = 1;

		mTimer += deltaTime;

		if(mTimer>=this->mAnims[this->mBaseAnimID]->getLength())
			mTimer=0;

		//if (mTopAnimID == ANIM_DRAW_SWORDS)
		//{
		//	// flip the draw swords animation if we need to put it back
		//	topAnimSpeed = mSwordsDrawn ? -1 : 1;

		//	// half-way through the animation is when the hand grasps the handles...
		//	if (mTimer >= mAnims[mTopAnimID]->getLength() / 2 &&
		//		mTimer - deltaTime < mAnims[mTopAnimID]->getLength() / 2)
		//	{
		//		// so transfer the swords from the sheaths to the hands
		//		mBodyEnt->detachAllObjectsFromBone();
		//		mBodyEnt->attachObjectToBone(mSwordsDrawn ? "Sheath.L" : "Handle.L", mSword1);
		//		mBodyEnt->attachObjectToBone(mSwordsDrawn ? "Sheath.R" : "Handle.R", mSword2);
		//		// change the hand state to grab or let go
		//		mAnims[ANIM_HANDS_CLOSED]->setEnabled(!mSwordsDrawn);
		//		mAnims[ANIM_HANDS_RELAXED]->setEnabled(mSwordsDrawn);

		//		// toggle sword trails
		//		if (mSwordsDrawn)
		//		{
		//			mSwordTrail->setVisible(false);
		//			mSwordTrail->removeNode(mSword1->getParentNode());
		//			mSwordTrail->removeNode(mSword2->getParentNode());
		//		}
		//		else
		//		{
		//			mSwordTrail->setVisible(true);
		//			mSwordTrail->addNode(mSword1->getParentNode());
		//			mSwordTrail->addNode(mSword2->getParentNode());
		//		}
		//	}

		//	if (mTimer >= mAnims[mTopAnimID]->getLength())
		//	{
		//		// animation is finished, so return to what we were doing before
		//		if (mBaseAnimID == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
		//		else
		//		{
		//			setTopAnimation(ANIM_RUN_TOP);
		//			mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
		//		}
		//		mSwordsDrawn = !mSwordsDrawn;
		//	}
		//}
		//else if (mTopAnimID == ANIM_SLICE_VERTICAL || mTopAnimID == ANIM_SLICE_HORIZONTAL)
		//{
		//	if (mTimer >= mAnims[mTopAnimID]->getLength())
		//	{
		//		// animation is finished, so return to what we were doing before
		//		if (mBaseAnimID == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
		//		else
		//		{
		//			setTopAnimation(ANIM_RUN_TOP);
		//			mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
		//		}
		//	}

		//	// don't sway hips from side to side when slicing. that's just embarrassing.
		//	if (mBaseAnimID == ANIM_IDLE_BASE) baseAnimSpeed = 0;
		//}
		//else if (mBaseAnimID == ANIM_JUMP_START)
		//{
		//	if (mTimer >= mAnims[mBaseAnimID]->getLength())
		//	{
		//		// takeoff animation finished, so time to leave the ground!
		//		setBaseAnimation(ANIM_JUMP_LOOP, true);
		//		// apply a jump acceleration to the character
		//		mVerticalVelocity = JUMP_ACCEL;
		//	}
		//}
		//else if (mBaseAnimID == ANIM_JUMP_END)
		//{
		//	if (mTimer >= mAnims[mBaseAnimID]->getLength())
		//	{
		//		// safely landed, so go back to running or idling
		//		if (mKeyDirection == Vector3::ZERO)
		//		{
		//			setBaseAnimation(ANIM_IDLE_BASE);
		//			setTopAnimation(ANIM_IDLE_TOP);
		//		}
		//		else
		//		{
		//			setBaseAnimation(ANIM_RUN_BASE, true);
		//			setTopAnimation(ANIM_RUN_TOP, true);
		//		}
		//	}
		//}

		// increment the current base and top animation times
		if (mBaseAnimID != ANIM_NONE) mAnims[mBaseAnimID]->addTime(deltaTime * baseAnimSpeed);
		//if (mTopAnimID != ANIM_NONE) mAnims[mTopAnimID]->addTime(deltaTime * topAnimSpeed);

		// apply smooth transitioning between our animations
		fadeAnimations(deltaTime);
	}

	void fadeAnimations(Real deltaTime)
	{
		for (int i = 0; i < NUM_ANIMS; i++)
		{
			if (mFadingIn[i])
			{
				// slowly fade this animation in until it has full weight
				Real newWeight = mAnims[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
				mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
				if (newWeight >= 1) mFadingIn[i] = false;
			}
			else if (mFadingOut[i])
			{
				// slowly fade this animation out until it has no weight, and then disable it
				Real newWeight = mAnims[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
				mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
				if (newWeight <= 0)
				{
					mAnims[i]->setEnabled(false);
					mFadingOut[i] = false;
				}
			}
		}
	}

	void updateCamera(Real deltaTime)
	{
		//		3.帧循环逻辑

		//更新角色
		//	取得按键方向矢量，根据这个矢量设置角色的positon，direction
		//更新摄相机
		//	将永远的中心月亮女神pivot放到角色的肩膀上。(女神的圣斗士goal会永远在pivot女神的正后方，，同时goal的猎杀者camNode也会死死紧逼)
		//	猎杀者camNode用自己的速度向goal前进一步
		//	猎杀者将视线对准月亮女神pivot(虽然postion是向goal逼近，但是方向却向着永远的中心月亮女神pivot)

		//至此chase摄像机的基本实现原理水落石出。无非就是女神的圣斗士被猎杀者时刻紧追，猎杀者死死的盯住女神用目光表示内容，用行动追逐女神的斗士。


		// place the camera pivot roughly at the character's shoulder
		mCameraPivot->setPosition(mBodyNode->getPosition() + Vector3::UNIT_Y * CAM_HEIGHT);


		////第一人称
		// //! 将pivot对准角色的正前方，注意此时相机的+Z必须和角色的+Z相反，因为相机时从+Z看向-Z的
  //  //! 这样修改后，就完成了一个第一人称的相机，和魔兽世界类似
  //  //! W键始终让角色往自身正前方走，而不是相机的正前方
  //  Vector3 front = mCameraPivot->getOrientation().zAxis();
  //  Vector3 goal  = -mBodyNode->getOrientation().zAxis();
  //  Quaternion toGoal = front.getRotationTo(goal);
  //  Real yawToGoal = toGoal.getYaw().valueDegrees();
  //  mCameraPivot->yaw(Degree(yawToGoal) , Node::TS_WORLD );
		////第一人称

		 //move the camera smoothly to the goal
		Vector3 goalOffset = mCameraGoal->_getDerivedPosition() - mCameraNode->getPosition();
		mCameraNode->translate(goalOffset * deltaTime * 9.0f);
		// always look at the pivot
		mCameraNode->lookAt(mCameraPivot->_getDerivedPosition(), Node::TS_WORLD);
	}

	void updateCameraGoal(Real deltaYaw, Real deltaPitch, Real deltaZoom)
	{//3个变量分别是当前mouse的xyz
		//yaw:绕y轴
		//pitch：绕x轴
		//roll:绕z轴
	//MouseMove事件影响
	//pitch ---  只影响pivot的pitch。
	//yaw ---    只影响pivot的yaw。
	//zoom --- 只影响goal的local postion，决定了goal与pivot的z向距离。goal永远在pivot的正后方，也就是只在pivot的z轴上移动。
	//
	//鼠标的移动只会造成pivot的yaw和pitch，以及goal的local-z的移动。同角色的移动是没有关系的。
	//最终的结果是改变了goal在world中的position和direction，这个作为camera在帧循环中处理的唯一依据。


		mCameraPivot->yaw(Degree(deltaYaw), Node::TS_WORLD);

		// bound the pitch
		if (!(mPivotPitch + deltaPitch > 25 && deltaPitch > 0) &&
			!(mPivotPitch + deltaPitch < -60 && deltaPitch < 0))
		{
			mCameraPivot->pitch(Degree(deltaPitch), Node::TS_LOCAL);
			mPivotPitch += deltaPitch;
		}
		//goal和pivot的距离
		Real dist = mCameraGoal->_getDerivedPosition().distance(mCameraPivot->_getDerivedPosition());
		Real distChange = deltaZoom * dist;

		// bound the zoom
		if (!(dist + distChange < 8 && distChange < 0) &&
			!(dist + distChange > 25 && distChange > 0))
		{
			mCameraGoal->translate(0, 0, distChange, Node::TS_LOCAL);
		}
	}

	void setBaseAnimation(AnimID id, bool reset = false)
	{
		if (mBaseAnimID >= 0 && mBaseAnimID < NUM_ANIMS)
		{
			// if we have an old animation, fade it out
			mFadingIn[mBaseAnimID] = false;
			mFadingOut[mBaseAnimID] = true;
		}

		mBaseAnimID = id;

		if (id != ANIM_NONE)
		{
			// if we have a new animation, enable it and fade it in
			mAnims[id]->setEnabled(true);
			//mine
			mAnims[id]->setTimePosition(mTimer);
			mAnims[id]->setWeight(0);
			mFadingOut[id] = false;
			mFadingIn[id] = true;
			if (reset) mAnims[id]->setTimePosition(0);
		}
	}

	//void setTopAnimation(AnimID id, bool reset = false)
	//{
	//	if (mTopAnimID >= 0 && mTopAnimID < NUM_ANIMS)
	//	{
	//		// if we have an old animation, fade it out
	//		mFadingIn[mTopAnimID] = false;
	//		mFadingOut[mTopAnimID] = true;
	//	}

	//	mTopAnimID = id;

	//	if (id != ANIM_NONE)
	//	{
	//		// if we have a new animation, enable it and fade it in
	//		mAnims[id]->setEnabled(true);
	//		mAnims[id]->setWeight(0);
	//		mFadingOut[id] = false;
	//		mFadingIn[id] = true;
	//		if (reset) mAnims[id]->setTimePosition(0);
	//	}
	//}

	void clampToTerrain()
{
	static Ogre::Ray updateRay;
	updateRay.setOrigin(this->mBodyNode->getPosition()+Ogre::Vector3(0,0,0));
	updateRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
	m_raySceneQuery->setRay(updateRay);
	Ogre::RaySceneQueryResult &Result= m_raySceneQuery->execute();

	if(Result.size() == 0)
	{
		updateRay.setOrigin(this->mBodyNode->getPosition());
		updateRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
		m_raySceneQuery->setRay(updateRay);
		Result = m_raySceneQuery->execute();
	}

	Ogre::RaySceneQueryResult ::iterator i=Result.begin();
	while(i!=Result.end()&&i->movable->getMovableType()!="Entity") i++;
	if(i!= Result.end()&& i->movable)
	{
		this->mBodyNode->setPosition(this->mBodyNode->getPosition().x,this->mBodyNode->getPosition().y+i->distance*m_raySceneQuery->getRay().getDirection().y ,this->mBodyNode->getPosition().z);
		//mCamera->setPosition(0,0,0);
	}
}

public:
	Ogre::AxisAlignedBox getAABB()
	{
		return mBodyNode->_getWorldAABB();
	}


	void setInfo(Ogre::String str)
	{
		monsterInfo->setCaption(str);
	}

	void setHurtInfo(Ogre::String str)
	{
		getHurt->setCaption(str);
	}

	
	Real getHP()
	{
		return this->HP;
	}
	void setHP(Real hp)
	{
		this->HP = hp;
	}

	Real getAttack()
	{
		Real attack = 0;

		if(mAnims[mBaseAnimID]->hasEnded())
		{
			switch(mBaseAnimID)
			{
			case ANIM_Attack_Special_02:
				attack = 9;
				break;
			case ANIM_Attack_Special_03:
				attack = 9;
				break;
			case ANIM_Attack_Special_04:
				attack = 11;
				break;
			case ANIM_Attack_Special_05:
				attack = 10;
				break;
			case ANIM_Attack_Special_06:
				attack = 6;
				break;
			case ANIM_Attack_Special_09:
				attack = 16;
				break;
			case ANIM_Attack_Special_10:
				attack = 12;
				break;
			case ANIM_Attack_Special_11:
				attack = 8;
				break;
			case ANIM_Attack_Special_12:
				attack = 13;
				break;
			case ANIM_Attack_Special_13:
				attack = 18;
				break;
			default:
				attack = 0;
			}
		}
		return attack;
	}

	bool ifdead()
	{
		if(HP <= 0)
		{
			setBaseAnimation(ANIM_Death_BASE);
			return true;
		}
		else return false;
	}
private:
	Ogre::MovableText* monsterInfo;
	Ogre::MovableText* getHurt;
	Camera* mCamera;
	RaySceneQuery * m_raySceneQuery;
	SceneNode* mBodyNode;
	SceneNode* mFighter;
	SceneNode* mCameraPivot;
	SceneNode* mCameraGoal;
	SceneNode* mCameraNode;
	Real mdistance;
	Real mPivotPitch;
	Entity* mBodyEnt;
	//Entity* mSword1;
	//Entity* mSword2;
	//RibbonTrail* mSwordTrail;
	AnimationState* mAnims[NUM_ANIMS];    // master animation list
	AnimID mBaseAnimID;                   // current base (full- or lower-body) animation
	//AnimID mTopAnimID;                    // current top (upper-body) animation
	bool mFadingIn[NUM_ANIMS];            // which animations are fading in
	bool mFadingOut[NUM_ANIMS];           // which animations are fading out
	//bool mSwordsDrawn;
	Vector3 mKeyDirection;      // player's local intended direction based on WASD keys
	Vector3 mGoalDirection;     // actual intended direction in world-space
	Real mVerticalVelocity;     // for jumping
	Real mTimer;                // general timer to see how long animations have been playing
	Real mAnimslevel[NUM_ANIMS];



	Real HP;
};

#endif
