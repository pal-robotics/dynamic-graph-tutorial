/*
 * Copyright 2010,
 * Florent Lamiraux
 *
 * CNRS
 *
 * This file is part of dynamic-graph-tutorial.
 * dynamic-graph-tutorial is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * dynamic-graph-tutorial is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.  You should
 * have received a copy of the GNU Lesser General Public License along
 * with dynamic-graph-tutorial.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DYNAMIC_GRAPH_TUTORIAL_TABLE_CART_HH
# define DYNAMIC_GRAPH_TUTORIAL_TABLE_CART_HH

# include <dynamic-graph/entity.h>
# include <dynamic-graph/signal-ptr.h>
# include <dynamic-graph/linear-algebra.h>

namespace dynamicgraph {
  namespace tutorial {

    /**
       \brief Table cart model

       This class represents the classical table-cart model as used as a
       simplified model for a humanoid robot.

       The equation of motion is:

       \f{eqnarray*}{
       \dot x  &=& \textbf{u}
       \f}

       where
       \li the state \f$x\f$ is the position of the cart on an horizontal axis
       represented by signal stateSOUT,
       \li the control is a vector of dimension 1 \f$\textbf{u}\f$ reprensented
       by signal controlSIN_.
       \li \f$m\f$ is the mass of the cart.

       The output of the system, represented by signal zmpSOUT is the center of
       pressure of the ground reaction force.

       \f{eqnarray*}{
       z &=& x - \frac {h}{g} (\ddot {x} + \frac {1}{m} F)
       \f}

       where
       \li \f$h\f$ is the height of the cart,
       \li \f$g\f$ is the gravity constant and
       \li \$F\f$ is a perturbation force.
       
    */

    class TableCart : public Entity
    {
      DYNAMIC_GRAPH_ENTITY_DECL ();
    public:
      /**
	 \brief Constructor by name
      */
      TableCart(const std::string& inName);

      ~TableCart();

      /// Integrate equation of motion over time step given as input
      void incr(double inTimeStep);

      /// \name Parameters
      /// @{

      /// \brief Set the mass of the cart
      void setCartMass (const double& inMass) {
	cartMass_ = inMass;
      }

      /// \brief Get the mass of the cart
      double getCartMass () const {
	return cartMass_;
      }

      /// \brief Set the height of the cart
      void setCartHeight (const double& inHeight) {
	cartHeight_ = inHeight;
      }

      /// \brief Get the height of the cart
      double getCartHeight () const {
	return cartHeight_;
      }

      /**
	 @}
      */

    private:
      /// Perturbation force acting on the table cart
      SignalPtr< double, int > forceSIN_;
      /// Control
      SignalPtr< ::dynamicgraph::Vector, int > controlSIN_;
      /// State of the table cart
      Signal< ::dynamicgraph::Vector, int> stateSOUT_;
      /// ZMP
      Signal< double, int> zmpSOUT_;

      /// \brief Mass of the cart
      double cartMass_;
      /// \brief Height of the cart
      double cartHeight_;
      /// \brief Viscosity coefficient
      double viscosity_;
      /// Control at previous iteration
      ::dynamicgraph::Vector prevControl_;
      /**
	 \brief Compute the evolution of the state of the pendulum
      */
      ::dynamicgraph::Vector
	  computeDynamics(const Vector& inState,
				  const Vector& inControl,
				  const double& inForce,
				  const Vector& inPrevControl,
				  double inTimeStep,
				  double& zmp);
    };
  } // namespace tutorial
} // namespace dynamicgraph
#endif // DYNAMIC_GRAPH_TUTORIAL_TABLE_CART_HH