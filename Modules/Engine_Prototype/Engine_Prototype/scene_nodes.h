#ifndef SCENENODES_H_
#define SCENENODES_H_

#include <vector>
#include "S3DMesh.h"

class SceneNode
{
private:

protected:
	S3DMesh* mesh = nullptr;
	SceneNode* parent = nullptr;
	std::vector<SceneNode*> children;

	glm::mat4 Parent_Matrix;
	glm::mat4 Model_Matrix;
	glm::vec3 axis;

	std::mutex Matrix_Mutex;

public:
	SceneNode( SceneNode* parent )
	{
		this->parent = parent;
		if ( parent )
		{
			parent->children.push_back( this );
		}
		Model_Matrix = glm::mat4( 1.f );
	}
	~SceneNode()
	{
		delete mesh;
		DeleteChildren();
	}
	void DeleteChildren()
	{
		for ( auto child : children )
		{
			delete child;
		}
		children.clear();
	}
	void Set_Mesh( S3DMesh* mesh )
	{
		this->mesh = mesh;
	}
	inline virtual void CopyParentMatrix()
	{
		//Matrix_Mutex.lock();
		Model_Matrix = parent->Model_Matrix;
		//Matrix_Mutex.unlock();
	}
	const glm::mat4& Get_Model_Matrix()
	{
		return Model_Matrix;
	}
	virtual void Trickle_Down_Data()
	{
		CopyParentMatrix();
		for ( auto child_node : children )
		{
			child_node->Trickle_Down_Data();
		}
	}
	virtual void Draw()
	{
		if ( mesh )
		{
			mesh->Draw( Model_Matrix );
		}
		for ( auto child_node : children )
		{
			child_node->Draw();
		}
	}
	virtual void Update( double& seconds )
	{
		CopyParentMatrix();
		for ( auto child_node : children )
		{
			child_node->Update( seconds );
		}
	}
};


class Root_SceneNode : public SceneNode
{
public:
	Root_SceneNode() : SceneNode( nullptr ){}
	void Trickle_Down_Data()
	{
		for ( auto child_node : children )
		{
			child_node->Trickle_Down_Data();
		}
	}
	void Draw()
	{
		for ( auto child_node : children )
		{
			child_node->Draw();
		}
	}
	void Update( double& seconds )
	{
		for ( auto child_node : children )
		{
			child_node->Update( seconds );
		}
	}
};


class TransformerNode : public virtual SceneNode
{
protected:
	float Speed = NULL;
	glm::mat4 Translation_Matrix;

public:
	TransformerNode( SceneNode* parent, bool x, bool y, bool z ) : SceneNode( parent )
	{
		axis.x = x ? 1 : 0;
		axis.y = y ? 1 : 0;
		axis.z = z ? 1 : 0;
		glm::normalize( axis );
		Translation_Matrix = glm::mat4( 1.f );
	}
	inline virtual void CopyParentMatrix()
	{
		SceneNode::CopyParentMatrix();
		Model_Matrix = Model_Matrix * Translation_Matrix;
	}
	virtual void Update( double& seconds )
	{
		if ( Speed != NULL )
		{
			Transform( Speed * seconds );
		}
		for ( auto child_node : children )
		{
			child_node->Update( seconds );
		}
	}
	void Transform( float Distance )
	{
		Translation_Matrix = glm::translate( Translation_Matrix, Distance * axis );
		Trickle_Down_Data();
	}
	void Transform( float Distance, glm::vec3 axis )
	{
		Translation_Matrix = glm::translate( Translation_Matrix, Distance * axis );
		Trickle_Down_Data();
	}
	void set_Axis( glm::vec3 axis )
	{
		this->axis = axis;
	}
	void set_Velocity( float Speed, glm::vec3 dir )
	{
		this->Speed = Speed;
		axis = dir;
		glm::normalize( axis );
	}
	void set_Speed( float Speed )
	{
		this->Speed = Speed;
	}
};


class RotatorNode : public virtual SceneNode
{
protected:
	float angle_per_sec = NULL;
	glm::mat4 Rotation_Matrix;

public:
	RotatorNode( SceneNode* parent, bool x, bool y, bool z ) : SceneNode( parent )
	{
		axis.x = x ? 1 : 0;
		axis.y = y ? 1 : 0;
		axis.z = z ? 1 : 0;
		glm::normalize( axis );
		Rotation_Matrix = glm::mat4( 1.f );
	}
	inline virtual void CopyParentMatrix()
	{
		SceneNode::CopyParentMatrix();
		Model_Matrix = Model_Matrix * Rotation_Matrix;
	}
	virtual void Update( double& seconds )
	{
		if ( angle_per_sec != NULL )
		{
			Rotate( angle_per_sec * seconds );
		}
		for ( auto child_node : children )
		{
			child_node->Update( seconds );
		}
	}
	void Rotate( float angle )
	{
		Rotation_Matrix = glm::rotate( Rotation_Matrix, (float)angle, axis );
		Trickle_Down_Data();
	}
	void Rotate( float angle, glm::vec3 axis )
	{
		Rotation_Matrix = glm::rotate( Rotation_Matrix, (float)angle, axis );
		Trickle_Down_Data();
	}
	void set_Axis( glm::vec3 axis )
	{
		this->axis = axis;
	}
	void set_RotationHz( float angle_per_sec )
	{
		this->angle_per_sec = angle_per_sec;
	}
};


class ScalarNode : public virtual SceneNode
{
protected:
	float ScalingRatio_PerSecond = NULL;
	glm::mat4 Scaling_Matrix;

public:
	ScalarNode( SceneNode* parent, bool x, bool y, bool z ) : SceneNode( parent )
	{
		axis.x = x ? 1 : 0;
		axis.y = y ? 1 : 0;
		axis.z = z ? 1 : 0;
		glm::normalize( axis );
		Scaling_Matrix = glm::mat4( 1.f );
	}
	inline virtual void CopyParentMatrix()
	{
		SceneNode::CopyParentMatrix();
		Model_Matrix = Model_Matrix * Scaling_Matrix;
	}
	virtual void Update( double& seconds )
	{
		if ( ScalingRatio_PerSecond != NULL )
		{
			Scale( ScalingRatio_PerSecond * seconds );
		}
		for ( auto child_node : children )
		{
			child_node->Update( seconds );
		}
	}
	void Scale( float scale )
	{
		Scaling_Matrix = glm::scale( Scaling_Matrix, scale * axis );
		Trickle_Down_Data();
	}
	void Scale( float scale, glm::vec3 axis )
	{
		Scaling_Matrix = glm::scale( Scaling_Matrix, scale * axis );
		Trickle_Down_Data();
	}
	void set_Axis( glm::vec3 axis )
	{
		this->axis = axis;
	}
	void set_ScalingHz( float ScalingRatio_PerSecond )
	{
		this->ScalingRatio_PerSecond = ScalingRatio_PerSecond;
	}
};


class Timer_Node : public virtual SceneNode
{
protected:
	std::chrono::duration<std::chrono::milliseconds> Timer_Length;
};


class Dynamic_Node : public virtual TransformerNode, public virtual RotatorNode, public virtual ScalarNode
{
public:
	Dynamic_Node( SceneNode* parent, bool x, bool y, bool z ) :
		SceneNode( parent ),
		TransformerNode( parent, x, y, z ),
		RotatorNode( parent, x, y, z ),
		ScalarNode( parent, x, y, z ) {}
	inline virtual void CopyParentMatrix()
	{
		SceneNode::CopyParentMatrix();
		Model_Matrix = Parent_Matrix * Model_Matrix;
	}
	virtual void Update( double& seconds )
	{
		if ( Speed != NULL )
		{
			Transform( Speed * seconds );
		}
		if ( angle_per_sec != NULL )
		{
			Rotate( angle_per_sec * seconds );
		}
		if ( ScalingRatio_PerSecond != NULL )
		{
			Scale( ScalingRatio_PerSecond * seconds );
		}
		Trickle_Down_Data();
	}
};


class Static_Node : public virtual Dynamic_Node
{
public:
	void Update( double& seconds )
	{
		CopyParentMatrix();
	}
};

class Animator_Node
{

};

#endif
