--[[
  Copyright (c) 2013 David Young dayoung@goliathdesigns.com

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
]]

function AgentUtilities_ApplyPhysicsSteeringForce(
    agent, steeringForce, deltaTimeInSeconds)

    -- Ignore very weak steering forces.
    if (Vector.LengthSquared(steeringForce) < 0.1) then
        return;
    end
    
    -- Agents with 0 mass are immovable.
    if (agent:GetMass() <= 0) then
        return;
    end

    -- Zero out any steering in the y direction
    steeringForce.y = 0;

    -- Maximize the steering force, essentially forces the agent to max acceleration.
    steeringForce = Vector.Normalize(steeringForce) * agent:GetMaxForce();

    -- Apply force to the physics representation.
    agent:ApplyForce(steeringForce);

    -- Newtons(kg*m/s^2) divided by mass(kg) results in acceleration(m/s^2).
    local acceleration = steeringForce / agent:GetMass();
    
    -- Velocity is measured in meters per second(m/s).
    local currentVelocity = agent:GetVelocity();
    
    -- Acceleration(m/s^2) multiplied by seconds results in velocity(m/s).
    local newVelocity = currentVelocity + (acceleration * deltaTimeInSeconds);

    -- Zero out any pitch changes to keep the Agent upright.
    -- NOTE: This implies that agents can immediately turn in any direction.
    newVelocity.y = 0;

    -- Point the agent in the direction of movement.
    agent:SetForward(newVelocity);
end

function AgentUtilities_ClampHorizontalSpeed(agent)
    local velocity = agent:GetVelocity();
    -- Store downward velocity to apply after clamping.
    local downwardVelocity = velocity.y;

    -- Ignore downward velocity since Agents never apply downward velocity
    -- themselves.
    velocity.y = 0;

    local maxSpeed = agent:GetMaxSpeed();
    local squaredSpeed = maxSpeed * maxSpeed;

    -- Using squared values avoids the cost of using the square 
    -- root when calculating the magnitude of the velocity vector.
    if (Vector.LengthSquared(velocity) > squaredSpeed) then
        local newVelocity = Vector.Normalize(velocity) * maxSpeed;

        -- Reapply the original downward velocity after clamping.
        newVelocity.y = downwardVelocity;

        agent:SetVelocity(newVelocity);
    end
end

function AgentUtilities_CreateAgentRepresentation(agent, height, radius)
    -- Capsule height and radius in meters.
    local capsule = Core.CreateCapsule(agent, height, radius);
    Core.SetMaterial(capsule, "Ground2");
end

function AgentUtilities_UpdatePosition(agent, deltaTimeInSeconds)
    -- Velocity(m/s) multiplied by seconds results in meters.
    local positionDelta = agent:GetVelocity() * deltaTimeInSeconds;
    
    -- Calculate the change in meters to the agents current position.
    local newPosition = agent:GetPosition() + positionDelta;
    
    -- Apply the change in position.
    agent:SetPosition(newPosition);
end
